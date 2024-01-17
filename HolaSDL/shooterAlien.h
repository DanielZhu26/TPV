#ifndef SHOOTERALIEN_H
#define SHOOTERALIEN_H
#include "../checkML.h"
#include "alien.h"

class Game;
class shooterAlien : public alien
{
private:
	static const int reloadTime = 300;
	Uint32 startTimer;
	Uint32 timer;
	bool canShoot;
public:
	shooterAlien(int x, int y, int type, int cooldown, Texture* textura, Mothership* motherShip, PlayState* playState);

	void update() override;

	void save(std::ofstream& out) const;
}; 
#endif 