#include "SceneObject.h"
#include "PlayState.h"

SceneObject::SceneObject(int x, int y, int width, int height, PlayState* gameState) : GameObject(gameState)
{
	pos = Point2D<int>(x, y);
	this->width = width;
	this->height = height;
	this->playState = gameState;
}

void SceneObject::setListAnchor(GameList<SceneObject, false>::anchor anchor)
{
	this->anchorSceneObject = anchor;
}