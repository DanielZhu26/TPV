#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H
#include "../checkML.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "SDL.h"

class PlayState;

class SceneObject : public GameObject
{
protected:
	Point2D<int> pos;
	int width;
	int height;

	PlayState* playState;
	GameList<SceneObject, false>::anchor anchorSceneObject;
public:
	SceneObject(int x, int y, int width, int height, PlayState* gameState);

	virtual ~SceneObject() {}

	void setListAnchor(GameList<SceneObject, false>::anchor anchor);

	GameList<SceneObject, false>::anchor getAnchor() { return anchorSceneObject; }

	virtual bool hit(SDL_Rect other, bool fromAlien) = 0;
};
#endif