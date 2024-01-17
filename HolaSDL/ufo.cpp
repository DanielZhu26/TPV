#include "ufo.h"
#include "PlayState.h"
#include "Game.h"

ufo::ufo(int x, int y, int state, int cooldown, Texture* textura, PlayState* playState)
	: SceneObject(x, y, textura->getFrameWidth(), textura->getFrameHeight(), playState)
{
	this->textura = textura;
	this->state = status(state);
	direction = x > width / 2 ? -1 : 1;

	spawnTimer = 0 - cooldown;
	destroyTimer = 0;
	timer = SDL_GetTicks();
	canSpawn = true;
}

ufo::~ufo()
{
	
}

void ufo::render() const
{
	if (state != status::hidden)
	{
		SDL_Rect rectDestino{ pos.getX(), pos.getY(), width, height };
		int frame = state == status::visible ? 0 : 1;
		textura->renderFrame(rectDestino, 0, frame);
	}
}

void ufo::update()
{
	timer = SDL_GetTicks();
	// si es visible moverse hasta salir por uno de los lados -> hidden
	if (state == status::visible)
	{
		pos = pos + Point2D<int>(1 * direction, 0);
		if (((pos + Point2D<int>(1 * direction, 0)).getX() > (playState->getGame()->getWidth()))
			|| ((pos + Point2D<int>(1 * direction, 0)).getX() < 0 - width))
		{
			state = status::hidden;
			direction = -direction;
			spawnTimer = SDL_GetTicks();
		}
	}
	// si el tiempo de cooldown de spawn se ha acabado,
	// probar un número aleatorio para ver si pasa a visible
	else if (state == status::hidden)
	{
		if ((timer - spawnTimer) > timeToSpawn && playState->getGame()->getRandomRange(0, 350) >= 350)
		{
			state = status::visible;
		}
	}
	// mostrar el frame de explosión hasta que pase el tiempo y luego
	// mover al ufo al borde correspondiente
	else if (state == status::destroyed)
	{
		if (timer - destroyTimer > timeToDestroy)
		{
			state = status::hidden;
			if (direction == 1)
				pos = Point2D<int>(playState->getGame()->getWidth(), pos.getY());
			else
				pos = Point2D<int>(0 - width, pos.getY());

			direction = -direction;
		}
	}
}

void ufo::save(std::ofstream& out) const
{
	out << 5 << " " << pos.getX() << " " << pos.getY() << " " << state << " " << (timer - spawnTimer) << endl;
}

bool ufo::hit(SDL_Rect other, bool fromAlien)
{
	if (state == status::visible)
	{
		SDL_Rect aux = SDL_Rect{ pos.getX(), pos.getY(), width, height };
		if (SDL_HasIntersection(&aux, &other) && !fromAlien)
		{
			state = status::destroyed;
			playState->addScore(100);
			playState->mayGrantReward(pos.getX() + width / 2, pos.getY());
			destroyTimer = SDL_GetTicks();
			return true;
		}
	}
	return false;
}