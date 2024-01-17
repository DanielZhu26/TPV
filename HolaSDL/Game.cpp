#include "Game.h"

Game::Game()
{
	//VARIABLES
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//INICIALIZAR SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		throw new runtime_error("Error cargando SDL");

	exit = false;
	textures = new Texture * [NUM_TEXTURES];

	//SDL variables
	this->window = window;
	this->renderer = renderer;

	CargarTexturas();

	stateMachine = new GameStateMachine(new MainMenuState(this));

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}
Game::~Game()
{
	delete stateMachine;
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		delete textures[i];
	}
	delete[] textures;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Game::Run()
{
	if (!stateMachine->isEmpty())
	{
		stateMachine->update();
		stateMachine->render();
		stateMachine->handleEvent();
	}
	return !stateMachine->isEmpty();
}

void Game::CargarTexturas()
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		this->textures[i] = new Texture(renderer, TEXTURE_DATA[i].filePath.c_str(), TEXTURE_DATA[i].rows, TEXTURE_DATA[i].cols);
	}
}

Texture* Game::getTexture(TextureName name) const
{
	return this->textures[name];
}


int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}