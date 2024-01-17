#ifndef GAME_H
#define GAME_H
#include "../checkML.h"
#include "texture.h"
#include <random>
#include "SDL.h"
#include "SDL_image.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"

using namespace std;
using uint = unsigned int;
enum GameOverType { exitWindow, error, gameOver, victory, saveGame};
enum TextureName { bunkerTex, cannonTex, alienTex,backgroundTex, ufoTex, numbersTex,
					mainMenuTex, bombTex, shieldRewardTex, shieldAppliedTex, 
					cargarPartida, codigo, continuar, gameOverTex, guardarPartida, 
					hasGanado, nuevaPartida, salir, volverAlMenu};

struct TextureData {
	TextureData(string filePath, int rows, int cols){
		this->filePath = filePath;
		this->rows = rows;
		this->cols = cols;
	}
	string filePath;
	int rows;
	int cols;
};
constexpr int NUM_TEXTURES = 19;
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int NUM_MAPS = 4;
const string filenames[NUM_MAPS]{ "mapas/original.txt","mapas/lluvia.txt","mapas/trinchera.txt", "mapas/urgente.txt" };
enum mapFilenames { original, lluvia, trinchera, urgente};
class Game
{
private:
	TextureData TEXTURE_DATA[NUM_TEXTURES] = {
		TextureData("texturas//bunker.png",1,4), TextureData("texturas//spaceship.png",1,1),
		TextureData("texturas//aliens.png",3,2), TextureData("texturas//stars.png",1,1),
		TextureData("texturas//ufo.png",1,2), TextureData("texturas//numbers.png",1,10),
		TextureData("fondos//mainMenu.png", 1, 1), TextureData("objetos//bomb.png", 1, 1),
		TextureData("objetos//shield_reward.png", 1, 1), TextureData("objetos//shield.png", 1, 1),
		TextureData("textos//cargarPartida.png", 1, 1), TextureData("textos//codigo.png", 1, 1),
		TextureData("textos//continuar.png", 1, 1), TextureData("textos//gameOver.png", 1, 1),
		TextureData("textos//guardarPartida.png", 1, 1), TextureData("textos//hasGanado.png", 1, 1),
		TextureData("textos//nuevaPartida.png", 1, 1), TextureData("textos//salir.png", 1, 1),
		TextureData("textos//volverAlMenu.png", 1, 1)
	};
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	Texture** textures;

	// flag para acabar el juego
	bool exit;

	GameStateMachine* stateMachine;

	mt19937_64 randomGenerator;

	void CargarTexturas();
public:
	Game();

	~Game();

	bool Run();

	GameStateMachine* getStateMachine() { return stateMachine; }

	Texture* getTexture(TextureName name) const;

	int getWidth() const { return WINDOW_WIDTH; }

	int getHeight() const { return WINDOW_HEIGHT; }

	SDL_Renderer* getRenderer() const { return renderer; }

	SDL_Window* getWindow() const { return window; }

	int getRandomRange(int min, int max);

	string getFilename(mapFilenames number) { return filenames[number]; }

	string getRandomFilename() { return filenames[getRandomRange(0, NUM_MAPS - 1)]; }
};
#endif