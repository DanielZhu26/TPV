#include "GameObject.h"
#include "GameState.h"

GameObject::GameObject(GameState* gameState)
{
	this->gameState = gameState;
}

void GameObject::setListAnchor(GameList<GameObject, true>::anchor anchor)
{
	this->anchor = anchor;
}