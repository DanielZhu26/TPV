#include <iostream>
#include <fstream>
#include <string>
#include "../checkML.h"
#include "SDL.h"
#include "SDL_image.h"
#include "texture.h"
#include "Vector2D.h"
#include "bunker.h"
#include "Game.h"
#include "customExceptions.h"
#include "PlayState.h"
#include "MainMenuState.h"

using namespace std;
using namespace customExceptions;
using uint = unsigned int;


int main(int argc, char* argv[])
{
	//main loop
	Game game;
	try 
	{
		while (game.Run())
			SDL_Delay(10);
	}
	catch (const InvadersError& exception)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "INVADERS ERROR", exception.what(), game.getWindow());
	}
	catch (...)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "ERROR INESPERADO", "", game.getWindow());
	}
	
	return 0;
}