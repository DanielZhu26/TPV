#include "PauseState.h"
#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"

PauseState::PauseState(Game* game, PlayState* playState) : GameState(game)
{
	this->playState = playState;
	list<EventHandler*> eventHandler;

	Button* botonContinuar = new Button(290, 120, game->getTexture(TextureName::continuar), this);
	botonContinuar->connect([this] {
		getGame()->getStateMachine()->popState(); });
	eventHandler.push_back(botonContinuar);

	Button* botonGuardarPartida = new Button(220, 220, game->getTexture(TextureName::guardarPartida), this);
	botonGuardarPartida->connect([this] {
		saving = true; });
	eventHandler.push_back(botonGuardarPartida);

	Button* botonCargarPartida = new Button(220, 320, game->getTexture(TextureName::cargarPartida), this);
	botonCargarPartida->connect([this] {
		loading = true; });
	eventHandler.push_back(botonCargarPartida);

	Button* botonSalir = new Button(340, 420, game->getTexture(TextureName::salir), this);
	botonSalir->connect([this] {
		getGame()->getStateMachine()->doblePopReplace(new MainMenuState(getGame())); });
	eventHandler.push_back(botonSalir);
	
	addObject(botonContinuar);
	addObject(botonGuardarPartida);
	addObject(botonCargarPartida);
	addObject(botonSalir);
	eventHandler.push_back(new PauseEventHandler(this));
	setEventHandler(eventHandler);

	loading = false;
	saving = false;
	code = -1;
}
void PauseState::render() const
{
	SDL_Delay(10);
	SDL_RenderClear(game->getRenderer());
	playState->render();
	SDL_Rect rectDestino{ 0, 0, game->getWidth(), game->getHeight() };
	SDL_SetRenderDrawColor(game->getRenderer(), 50, 50, 50, 120);
	SDL_RenderFillRect(game->getRenderer(), &rectDestino);
	GameState::render();
	if (saving || loading)
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

		int aux = code;
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

void PauseState::addNumber(int number)
{
	string aux = to_string(code);
	if (aux.length() < 5)
	{
		if (code == -1)
			code = number;
		else
		{
			aux = aux + to_string(number);
			code = stoi(aux);
		}
	}
}

void PauseState::removeNumber()
{
	code = code / 10;
}

void PauseState::PauseEventHandler::handleEvent(SDL_Event& event)
{
	
	if (event.type == SDL_KEYDOWN)
	{
		if (pauseState->loading || pauseState->saving)
		{
			if (event.key.keysym.sym > 47 && event.key.keysym.sym < 58)
			{
				pauseState->addNumber(event.key.keysym.sym - 48);
			}
			else if (event.key.keysym.sym == SDLK_BACKSPACE)
			{
				pauseState->removeNumber();
			}
			else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
			{
				if (pauseState->loading)
				{
					pauseState->getGame()->getStateMachine()->doblePopReplace(new PlayState(pauseState->getGame(), "saves/saved" + to_string(pauseState->code) + ".txt", 0));
				}
				else
				{
					pauseState->playState->saveGame("saves/saved" + to_string(pauseState->code) + ".txt");
					pauseState->saving = false;
					pauseState->code = NULL;
				}
					
			}
		}
		if (event.key.keysym.sym == SDLK_ESCAPE)
			pauseState->getGame()->getStateMachine()->popState();
	}
	else if (event.type == SDL_QUIT)
	{
		pauseState->getGame()->getStateMachine()->vaciarStates();
	}
}