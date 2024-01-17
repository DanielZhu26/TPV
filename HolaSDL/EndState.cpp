#include "EndState.h"
#include "Game.h"

EndState::EndState(Game* game) : GameState(game)
{
	list<EventHandler*> eventHandler;
	eventHandler.push_back(new EndEventHandler(this));

	Button* botonVolverMenu = new Button(240, 300, game->getTexture(TextureName::volverAlMenu), this);
	botonVolverMenu->connect([game, this]() {
		game->getStateMachine()->replaceState(new MainMenuState(game)); });
	eventHandler.push_back(botonVolverMenu);
	Button* botonSalir = new Button(340, 450, game->getTexture(TextureName::salir), this);
	botonSalir->connect([game, this]() {
		game->getStateMachine()->vaciarStates(); });
	eventHandler.push_back(botonSalir);


	addObject(botonVolverMenu);
	addObject(botonSalir);
	setEventHandler(eventHandler);
}

void EndState::render() const
{
	SDL_RenderClear(game->getRenderer());
	SDL_Rect rectDestino{ 290, 150, game->getTexture(TextureName::gameOverTex)->getFrameWidth(),game->getTexture(TextureName::gameOverTex)->getFrameHeight() };
	SDL_SetTextureColorMod(game->getTexture(TextureName::gameOverTex)->getSDLTexture(), 255, 0, 0);
	game->getTexture(TextureName::gameOverTex)->renderFrame(rectDestino, 0, 0);

	GameState::render();
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderPresent(game->getRenderer());
}

void EndState::update()
{

}

void EndState::EndEventHandler::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
	{
		endState->getGame()->getStateMachine()->replaceState(new MainMenuState(endState->getGame()));
	}
}