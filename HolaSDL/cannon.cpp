#include "cannon.h"
#include "PlayState.h"
#include "Game.h"
#include "EndState.h"

cannon::cannon(int x, int y, int hits, int cooldownLaser, Texture* textura, PlayState* playState) 
	: SceneObject(x, y, textura->getFrameWidth(), textura->getFrameHeight(), playState)
{
	this->hits = 3 - hits;
	this->maxHits = 3;
	this->textura = textura;
	direction = 0;
	startTimer = 0 - cooldownLaser;
	timer = SDL_GetTicks();
	canShoot = true;
	shield = false;
	texturaShield = playState->getGame()->getTexture(TextureName::shieldAppliedTex);
}

cannon::~cannon()
{

}

void cannon::render() const
{
	SDL_Rect rectDestino{ pos.getX(), pos.getY(), 34, 21 };
	textura->renderFrame(rectDestino,0,0);
	if (shield)
	{
		rectDestino = { pos.getX() - 4, pos.getY() - 10, texturaShield->getFrameWidth(), texturaShield->getFrameHeight() };
		texturaShield->renderFrame(rectDestino, 0, 0);
	}
}

void cannon::update()
{
	Point2D<int> aux(direction * speed, 0);

	if (((pos + aux).getX() < gameState->getGame()->getWidth() - textura->getFrameWidth()) &&
		((pos + aux).getX() > 0))
		pos = pos + aux;

	timer = SDL_GetTicks();
	// cooldown del laser
	if (!canShoot)
	{
		if (timer - startTimer >= laserCooldown)
		{
			canShoot = true;
		}
	}
	//cooldown del escudo
	if (shield)
	{
		if (timer - startTimerShield >= shieldTime)
		{
			shield = false;
		}
	}
}

void cannon::save(std::ofstream& out) const
{
	out << "0" << " " << pos.getX() << " " << pos.getY() << " " << (3 - hits) << " " << (timer - startTimer) << endl;
}

bool cannon::hit(SDL_Rect other, bool fromAlien)
{
	SDL_Rect aux = { pos.getX(), pos.getY(), width, height };
	if (SDL_HasIntersection(&other, &aux) && fromAlien)
	{
		if (shield)
			return true;
		else
		{
			hits++;
			shieldEffect(2000);
			// devolvemos al player al medio
			pos = Point2D<int>(gameState->getGame()->getWidth() / 2, pos.getY());
			if (hits >= maxHits)
				gameState->getGame()->getStateMachine()->replaceState(new EndState(gameState->getGame()));
				return true;
		}
	}
	return false;
}

void cannon::shieldEffect(int shieldTime)
{
	startTimerShield = SDL_GetTicks();
	this->shieldTime = shieldTime;
	shield = true;
}

void cannon::instantHit()
{
	hits++;
	if (hits >= maxHits)
		gameState->getGame()->getStateMachine()->replaceState(new EndState(gameState->getGame()));
}

cannon::PlayerEventHandler::PlayerEventHandler(cannon* player)
{
	this->player = player;
}

void cannon::PlayerEventHandler::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			player->direction = 1;
			break;
		case SDLK_LEFT:
			player->direction = -1;
			break;
		case SDLK_SPACE:
			// aux = posicion donde debe spawnear el laser (mitad de la nave y en la punta)
			Point2D<int> aux(player->pos.getX() + (player->width / 2), player->pos.getY());

			if (player->canShoot)
			{
				player->playState->fireLaser(aux, Color::rojo);
				// activamos cooldown
				player->canShoot = false;
				player->startTimer = SDL_GetTicks();
			}
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
			player->direction = 0;
	}
}