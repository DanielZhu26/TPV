#ifndef CANNON_H
#define CANNON_H
#include "../checkML.h"
#include "texture.h"
#include "SDL_image.h"
#include "SceneObject.h"
#include "laser.h"
#include "EventHandler.h"

class PlayState;
class Game;
class EndState;

class cannon : public SceneObject
{
private:
	static const int speed = 2;
	Texture* textura;
	Texture* texturaShield;
	int hits;
	int maxHits;
	int direction;

	bool shield;
	int shieldTime;

	bool canShoot;
	Uint32 startTimer;
	Uint32 startTimerShield;
	Uint32 timer;
	static const int laserCooldown = 600;

public:
	cannon(int x, int y, int hits, int cooldownLaser, Texture* textura, PlayState* playState);

	~cannon() override;

	void render() const override;
	
	void update() override;

	void save(std::ofstream& out) const;

	bool hit(SDL_Rect other, bool fromAlien) override;

	void shieldEffect(int shieldTime);

	int GetLives() { return maxHits - hits; }

	SDL_Rect getRect() { return SDL_Rect{ pos.getX(), pos.getY(), width, height }; }

	void instantHit();

	class PlayerEventHandler : public EventHandler
	{
	private:
		cannon* player;
	public:
		PlayerEventHandler(cannon* player);

		void handleEvent(SDL_Event& event) override;
	};
};
#endif