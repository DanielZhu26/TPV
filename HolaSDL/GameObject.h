#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "../checkML.h"
#include <fstream>
#include <iostream>
#include "gameList.h"

class GameState;

class GameObject
{
protected:
	GameState* gameState;
	GameList<GameObject, true>::anchor anchor;
public:
	GameObject(GameState* gameState);

	virtual ~GameObject() {}

	void setListAnchor(GameList<GameObject, true>::anchor anchor);

	GameList<GameObject, true>::anchor getAnchor() { return anchor; }

	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void save(std::ofstream& out) const = 0;
};
#endif