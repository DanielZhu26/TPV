#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "../checkML.h"
#include <list>
#include "gameList.h"
#include "GameObject.h"
#include "GameState.h"
#include "EventHandler.h"

class Game;

class GameState
{
protected:
	GameList<GameObject, true> objects;
	std::list<EventHandler*> eventHandler;
	Game* game;
public:
	GameState(Game* game);

	virtual ~GameState();

	virtual void update();

	virtual void render() const;

	virtual void hasDied(GameList<GameObject, true>::anchor anchor);

	void handleEvent(SDL_Event& event);

	void addEventListener();

	void setEventHandler(std::list<EventHandler*> eventHandler);

	void addObject(GameObject* newObject);

	Game* getGame() const { return game; }

	void clearEventHandler() { eventHandler.clear(); }
};
#endif