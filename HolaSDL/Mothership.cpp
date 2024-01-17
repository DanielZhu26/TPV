#include "Mothership.h"
#include "PlayState.h"
#include "alien.h"
#include "Game.h"
#include "EndState.h"

Mothership::Mothership(int direction, int level, int cooldown, PlayState* playState)
	: GameObject(playState)
{
	this->playState = playState;
	this->direction = direction;
	this->level = level;
	cannotMoveCalled = false;
	canLowerAliens = false;

	startTimer = - cooldown;
	timer = SDL_GetTicks();
	timeToMove = levelSpeeds[level];
	alienFrame = false;
	canMove = false;
}

Mothership::~Mothership()
{

}

void Mothership::cannotMove()
{
	cannotMoveCalled = true;
}


void Mothership::lowerAliens()
{
	direction = -direction;
	level++;
	if (level == 11)
	{
		gameState->getGame()->getStateMachine()->replaceState(new EndState(gameState->getGame()));
	}
	else
	{
		timeToMove = levelSpeeds[level];
		canLowerAliens = true;
		cannotMoveCalled = false;
	}
}

void Mothership::alienDied()
{
	numAliens--;
}

void Mothership::update()
{
	canMove = false;
	canLowerAliens = false;
	timer = SDL_GetTicks();
	if (timer - startTimer >= timeToMove)
	{
		startTimer = SDL_GetTicks();
		if (cannotMoveCalled)
		{
			lowerAliens();
		}
		canMove = true;
		alienFrame = !alienFrame;
	}
	if (numAliens < 1)
		gameState->getGame()->getStateMachine()->replaceState(new PlayState(gameState->getGame(), gameState->getGame()->getRandomFilename(), playState->getScore()));
}

void Mothership::render() const
{

}
void Mothership::save(std::ofstream& out) const
{
	out << 3 << " " << direction << " " << level << " " << (timer - startTimer) << endl;
}