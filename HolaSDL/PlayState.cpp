#include "PlayState.h"
#include "Game.h"

PlayState::PlayState(Game* game, string filename, int score) : GameState(game)
{
	loadScene(filename);
	list<EventHandler*> eventHandler;
	eventHandler.push_back(new cannon::PlayerEventHandler(this->player));
	eventHandler.push_back(new PlayStateEventHandler(this));
	setEventHandler(eventHandler);

	addScore(score);
}
PlayState::~PlayState() {
	delete mothership;
}
void PlayState::render() const
{
	SDL_RenderClear(game->getRenderer());
	game->getTexture(TextureName::backgroundTex)->render();
	for (SceneObject& object : sceneObjects)
		object.render();

	infoBar->render();
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderPresent(game->getRenderer());
}

void PlayState::update()
{
	mothership->update();
	for (GameObject& object : objects)
	{
		object.update();
	}
	infoBar->update();
}

void PlayState::hasDied(GameList<SceneObject, false>::anchor anchor, GameList<GameObject, true>::anchor anchor2)
{
	sceneObjects.erase(anchor);
	objects.erase(anchor2);
}

bool PlayState::damage(SDL_Rect damageZone, bool fromAlien)
{
	if (fromAlien && player->hit(damageZone, fromAlien))
		return true;
	for (SceneObject& object : sceneObjects)
	{
		if (object.hit(damageZone, fromAlien))
			return true;
	}
	return false;
}

void PlayState::fireLaser(Point2D<int> pos, char color)
{
	// añadimos laser a lista sceneobjects
	laser* aux = new laser(pos.getX(), pos.getY(), color, this);
	sceneObjects.push_back(aux);
	objects.push_back(aux);
}

void PlayState::addScore(int score)
{
	infoBar->addScore(score);
}

void PlayState::saveGame(string filename)
{
	ofstream archivo(filename);

	if (archivo.is_open())
	{
		mothership->save(archivo);
		for (GameObject& object : objects)
		{
			object.save(archivo);
		}
		archivo.close();
	}
	else
	{
		throw customExceptions::FileNotFoundError("Fallo al guardar el archivo");
	}
}
void PlayState::loadScene(string filename)
{
	ifstream archivo(filename);
	if (!archivo.is_open())
		throw customExceptions::FileNotFoundError(filename.c_str());

	int tipoObjeto;
	int x;
	int y;

	mothership = nullptr;
	int numAliens = 0;

	int scorePoints = 0;
	int index = -1;
	while (!archivo.eof())
	{
		archivo >> tipoObjeto;
		index++;

		if (archivo)
		{
			if (typeid(tipoObjeto) != typeid(int))
				throw customExceptions::FileFormatError(filename.c_str(), index);

			if (tipoObjeto == 0) // cannon
			{
				int numVidas;
				int cooldownLaser;
				archivo >> x;
				archivo >> y;
				archivo >> numVidas;
				archivo >> cooldownLaser;
				player = new cannon(x, y, numVidas, cooldownLaser, game->getTexture(TextureName::cannonTex), this);
				sceneObjects.push_back(player);
				objects.push_back(player);
			}
			else if (tipoObjeto == 1) // alien
			{
				if (mothership == nullptr)
					mothership = new Mothership(1, 0, 0, this);
				int tipoAlien;
				archivo >> x;
				archivo >> y;
				archivo >> tipoAlien;
				alien* aux = new alien(x, y, tipoAlien, game->getTexture(TextureName::alienTex), mothership, this);
				sceneObjects.push_back(aux);
				objects.push_back(aux);
				numAliens++;
			}
			else if (tipoObjeto == 2) // shooterAlien
			{
				if (mothership == nullptr)
					mothership = new Mothership(1, 0, 0, this);
				int tipoAlien;
				int cooldown;
				archivo >> x;
				archivo >> y;
				archivo >> tipoAlien;
				archivo >> cooldown;
				shooterAlien* aux = new shooterAlien(x, y, tipoAlien, cooldown, game->getTexture(TextureName::alienTex), mothership, this);
				sceneObjects.push_back(aux);
				objects.push_back(aux);
				numAliens++;
			}
			else if (tipoObjeto == 3) // mothership
			{
				int direction;
				int level;
				int cooldown;
				archivo >> direction;
				archivo >> level;
				archivo >> cooldown;
				mothership = new Mothership(direction, level, cooldown, this);
			}
			else if (tipoObjeto == 4) // bunker
			{
				int hits;
				archivo >> x;
				archivo >> y;
				archivo >> hits;
				bunker* aux = new bunker(x, y, hits - 4, game->getTexture(TextureName::bunkerTex), this);
				sceneObjects.push_back(aux);
				objects.push_back(aux);
			}
			else if (tipoObjeto == 5) // ovni
			{
				int state;
				int cooldown;
				archivo >> x;
				archivo >> y;
				archivo >> state;
				archivo >> cooldown;
				ufo* aux = new ufo(x, y, state, cooldown, game->getTexture(TextureName::ufoTex), this);
				sceneObjects.push_back(aux);
				objects.push_back(aux);
			}
			else if (tipoObjeto == 6) // laser
			{
				int asciiCharColor;
				archivo >> x;
				archivo >> y;
				archivo >> asciiCharColor;
				laser* aux = new laser(x, y, asciiCharColor == 114 ? 'r' : 'a', this);
				sceneObjects.push_back(aux);
				objects.push_back(aux);
			}
			else if (tipoObjeto == 7) // infobar
			{
				archivo >> scorePoints;
			}
		}
	}
	// infobar
	infoBar = new InfoBar(scorePoints, game->getTexture(TextureName::cannonTex), game->getTexture(TextureName::numbersTex), this);
	objects.push_back(infoBar);
	mothership->setNumAliens(numAliens);
}

void PlayState::mayGrantReward(int x, int y)
{
	int selection = game->getRandomRange(0, 2);

	if (selection == 1)
	{
		Shield* aux = new Shield(x, y, game->getTexture(TextureName::shieldRewardTex), player, this);
		sceneObjects.push_back(aux);
		objects.push_back(aux);
	}
	else if (selection == 2)
	{
		Bomb* aux = new Bomb(x, y, game->getTexture(TextureName::bombTex), player, this);
		sceneObjects.push_back(aux);
		objects.push_back(aux);
	}
}

PlayState::Bomb::Bomb(int x, int y, Texture* textura, cannon* player, PlayState* playState)
	: Reward(x, y, textura, player, playState)
{
	connect([player, this]() {
		lives--;
		player->instantHit();
		});
}

void PlayState::Bomb::update()
{
	pos = pos + Point2D<int>(0, 1);
	if ((pos - Point2D<int>(0, 1)).getY() > playState->getGame()->getHeight() + height)
		delete this;
	else
	{
		SDL_Rect aux = SDL_Rect{ pos.getX(), pos.getY(), width, height };
		if (SDL_HasIntersection(&aux, &player->getRect()))
		{
			callBack();
			if (lives < 1)
				delete this;
		}
	}
}

PlayState::Shield::Shield(int x, int y, Texture* textura, cannon* player, PlayState* playState) 
	: Reward(x, y, textura, player, playState)
{
	connect([player, this]() {
		player->shieldEffect(shieldTime);
		});
}

void PlayState::PlayStateEventHandler::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			playState->getGame()->getStateMachine()->pushState(new PauseState(playState->getGame(), playState));
		}
	}
	else if (event.type == SDL_QUIT)
	{
		playState->getGame()->getStateMachine()->popState();
	}
}
