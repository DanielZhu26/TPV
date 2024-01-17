#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include "../checkML.h"
#include "SDL.h"
class EventHandler
{
public:
	virtual void handleEvent(SDL_Event& event) = 0;
};
#endif