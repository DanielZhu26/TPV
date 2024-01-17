#ifndef ALIEN_H
#define ALIEN_H
#include "../checkML.h"
#include "texture.h"
#include "SDL_image.h"
#include "SceneObject.h"

class Mothership;
class PlayState;
class Game;

class alien : public SceneObject
{
private:
	Texture* textura;
	Mothership* mothership;
	int type;
public:
	alien(int x, int y, int type, Texture* textura, Mothership* mothership, PlayState* playState);

	~alien() override;

	void render() const override;

	void update() override;

	void save(std::ofstream& out) const;

	bool hit(SDL_Rect other, bool fromAlien) override;
};
#endif