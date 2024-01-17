#ifndef BUNKER_H
#define BUNKER_H
#include "../checkML.h"
#include "texture.h"
#include "SDL_image.h"
#include "SceneObject.h"

class PlayState;

class bunker : public SceneObject
{
private:
	static const int maxHits = 3;
	int hits;
	Texture* textura;
public:
	bunker(int x, int y, int currentHits, Texture* textura, PlayState* playState);

	~bunker() override;

	void render() const override;

	void update() override;

	void save(std::ofstream& out) const;

	bool hit(SDL_Rect other, bool fromAlien) override;
};
#endif