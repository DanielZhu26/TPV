#ifndef UFO_H
#define UFO_H
#include "../checkML.h"
#include "texture.h"
#include "SDL_image.h"
#include "SceneObject.h"

class PlayState;
class Game;

enum status { hidden, visible, destroyed };
class ufo : public SceneObject
{
private:
	Texture* textura;
	status state;
	int direction;

	static const int timeToSpawn = 5000;
	static const int timeToDestroy = 1000;
	Uint32 spawnTimer;
	bool canSpawn;
	Uint32 destroyTimer;
	Uint32 timer;
public:
	ufo(int x, int y, int state, int cooldown, Texture* textura, PlayState* playState);

	~ufo();

	void render() const override;

	void update() override;

	void save(std::ofstream& out) const;

	bool hit(SDL_Rect other, bool fromAlien) override;
};
#endif
