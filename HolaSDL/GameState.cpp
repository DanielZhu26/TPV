#include "GameState.h"
#include "Game.h"

GameState::GameState(Game* game)
{
	this->game = game;
}

GameState::~GameState()
{
	eventHandler.clear();
}

void GameState::update()
{
	for (auto& obj : objects)
	{
		obj.update();
	}
}

void GameState::render() const
{
	for (auto& obj : objects)
	{
		obj.render();
	}
}

void GameState::hasDied(GameList<GameObject, true>::anchor anchor)
{
	objects.erase(anchor);
}

void GameState::handleEvent(SDL_Event& event)
{
	for (EventHandler* e : eventHandler)
	{
		e->handleEvent(event);
	}
}

void GameState::addEventListener()
{

}

void GameState::addObject(GameObject* newObject)
{
	objects.push_back(newObject);
}

void GameState::setEventHandler(list<EventHandler*> eventHandler)
{
	this->eventHandler = eventHandler;
}