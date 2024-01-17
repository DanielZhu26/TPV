#include "shooterAlien.h"
#include "PlayState.h"
#include "game.h"

shooterAlien::shooterAlien(int x, int y, int type, int cooldown, Texture* textura, Mothership* mothership, PlayState* playState)
	: alien(x, y, type, textura, mothership, playState)
{
	startTimer = 0 - cooldown;
	timer = SDL_GetTicks();
	canShoot = false;
}

void shooterAlien::update()
{
	alien::update();

	timer = SDL_GetTicks();
	if (!canShoot)
	{
		timer = SDL_GetTicks();
		if (timer - startTimer >= reloadTime)
		{
			canShoot = true;
		}
	}
	else if (canShoot && playState->getGame()->getRandomRange(0, 350) == 350)
	{
		playState->fireLaser(Point2D<int>(pos.getX() + (width / 2), pos.getY()), Color::azul);
		startTimer = SDL_GetTicks();
		canShoot = false;
	}
}

void shooterAlien::save(std::ofstream& out) const
{
	out << 2 << " " << pos.getX() << " " << pos.getY() << " " << 0 << " " << (timer - startTimer) << endl;
}