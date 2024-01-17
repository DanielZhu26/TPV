#include "MainMenuState.h"
#include "Game.h"

MainMenuState::MainMenuState(Game* game) : GameState(game)
{
	list<EventHandler*> eventHandler;
	eventHandler.push_back(new MainMenuEventHandler(this));

	Button* botonNuevaPartida = new Button(240, 150, game->getTexture(TextureName::nuevaPartida), this);
	botonNuevaPartida->connect([game, this]() {
		game->getStateMachine()->replaceState(new PlayState(game, game->getRandomFilename(), 0)); });
	eventHandler.push_back(botonNuevaPartida);

	Button* botonSalir = new Button(330, 250, game->getTexture(TextureName::salir), this);
	botonSalir->connect([game]() {
		game->getStateMachine()->popState(); });
	eventHandler.push_back(botonSalir);

	Button* botonCargarPartida = new Button(230, 200, game->getTexture(TextureName::cargarPartida), this);
	botonCargarPartida->connect([game, this]() {
		LoadGame(); });
	eventHandler.push_back(botonCargarPartida);

	addObject(botonNuevaPartida);
	addObject(botonCargarPartida);
	addObject(botonSalir);
	setEventHandler(eventHandler);
}

MainMenuState::~MainMenuState() {

}



void MainMenuState::LoadGame()
{
	loading = true;
	loadCode = -1;
	pendingEventHandlerChange = true; // para que en el eventhandler no pete
}

void MainMenuState::render() const
{
	SDL_RenderClear(game->getRenderer());
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	game->getTexture(TextureName::mainMenuTex)->render();
	GameState::render();
	if (loading)
	{
		SDL_Rect rectDestino = { 169, 139, 462, 162 };
		SDL_SetRenderDrawColor(game->getRenderer(), 50, 255, 50, 255);
		SDL_RenderFillRect(game->getRenderer(), &rectDestino);
		rectDestino = { 170, 140, 460, 160 };
		SDL_SetRenderDrawColor(game->getRenderer(), 50, 50, 50, 255);
		SDL_RenderFillRect(game->getRenderer(), &rectDestino);
		rectDestino = { 315, 160,
			game->getTexture(TextureName::codigo)->getFrameWidth(), game->getTexture(TextureName::codigo)->getFrameHeight() };
		game->getTexture(TextureName::codigo)->renderFrame(rectDestino, 0, 0);

		int aux = loadCode;
		if (aux != -1)
		{
			int digito;
			// el añadido es para que esté centrado siempre
			int padding = 400 + (to_string(aux).length() * 15);
			int i = 1;
			while ((log10(aux) + 1 > 0)) {
				digito = aux % 10;
				SDL_Rect rectDestino{ padding - game->getTexture(TextureName::numbersTex)->getFrameWidth() * i, 200,
					game->getTexture(TextureName::numbersTex)->getFrameWidth(),game->getTexture(TextureName::numbersTex)->getFrameHeight() };
				game->getTexture(TextureName::numbersTex)->renderFrame(rectDestino, 0, digito);
				aux = aux / 10;
				i++;
			}
		}
	}
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderPresent(game->getRenderer());
}

void MainMenuState::update()
{
	// cambiamos los eventHandler en el siguiente update para evitar accesos indebidos
	if (pendingEventHandlerChange)
	{
		// quitamos los eventhandler antiguos y ponemos el de load
		list<EventHandler*> newEventHandler;
		newEventHandler.push_back(new LoadGameEventHandler(this));
		eventHandler.clear();
		setEventHandler(newEventHandler);
		// pintamos la pantalla oscura
		SDL_SetTextureColorMod(game->getTexture(TextureName::mainMenuTex)->getSDLTexture(), 140, 140, 140);
	}
}

void MainMenuState::addNumber(int number)
{
	string aux = to_string(loadCode);
	if (aux.size() < 5)
	{
		if (stoi(aux) == -1)
			loadCode = number;
		else
		{
			aux = aux + to_string(number);
			loadCode = stoi(aux);
		}
		
	}	
}

void MainMenuState::removeNumber()
{
	loadCode = loadCode / 10;
}

void MainMenuState::LoadGameEventHandler::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym > 47 && event.key.keysym.sym < 58)
		{
			mainMenuState->addNumber(event.key.keysym.sym - 48);
		}
		else if (event.key.keysym.sym == SDLK_BACKSPACE)
			mainMenuState->removeNumber();
		else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
		{
			SDL_SetTextureColorMod(mainMenuState->game->getTexture(TextureName::mainMenuTex)->getSDLTexture(), 255, 255, 255);
			mainMenuState->getGame()->getStateMachine()->replaceState(new PlayState(mainMenuState->getGame(), "saves/saved" + to_string(mainMenuState->getLoadCode()) + ".txt", 0));
		}
	}
	else if (event.type == SDL_QUIT)
	{
		mainMenuState->getGame()->getStateMachine()->popState();
	}
}

void MainMenuState::MainMenuEventHandler::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_QUIT)
	{
		mainMenuState->getGame()->getStateMachine()->popState();
	}
}