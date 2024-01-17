#ifndef LASER_H
#define LASER_H
#include "../checkML.h"
#include "Vector2D.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SceneObject.h"

class Game;
class PlayState;
class alien;

enum Color {azul = 'a', rojo = 'r' };

class laser : public SceneObject
{
private:
	static const int laserWidth = 4;
	static const int laserHeight = 20;
	static const int speed = 2;

	Color color;
public: 
	laser(int x, int y, char color, PlayState* playState);

	~laser() override;

	void render() const override;

	void update() override;

	void save(std::ofstream& out) const;

	bool hit(SDL_Rect other, bool fromAlien) override;

	bool isFromAlien() { return color == Color::azul; }
};
#endif