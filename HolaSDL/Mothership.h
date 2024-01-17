#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H
#include "../checkML.h"
#include "alien.h"
#include "GameObject.h"
#include <list>
using namespace std;

class EndState;
class PlayState;
class alien;

class Mothership : public GameObject
{
protected:
	PlayState* playState;
	int numAliens;
	int direction;
	bool cannotMoveCalled;
	bool canMove;
	bool canLowerAliens;

	int level;
	const int levelSpeeds[12] = { 1000, 750, 500, 250, 150, 125, 100, 75, 50, 50, 50 };

	// para mover a trompicones
	static const int alienMoveDistance = 10;
	bool alienFrame;
	Uint32 startTimer;
	Uint32 timer;
	Uint32 timeToMove;
public:
	Mothership(int direction, int level, int cooldown, PlayState* playState);

	~Mothership();

	void render() const override;

	void update() override;

	void save(std::ofstream& out) const;

	void lowerAliens();

	void cannotMove();

	void alienDied();

	int getAlienMoveDistance() const { return alienMoveDistance; }

	int getAlienFrame() const { return alienFrame ? 0 : 1; }

	bool shouldMove() const { return canMove; }

	bool shouldLower() const { return canLowerAliens; }

	int getDirection() const { return direction; }

	void setNumAliens(int num) { numAliens = num; }
};
#endif