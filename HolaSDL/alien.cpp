#include "alien.h"
#include "PlayState.h"
#include "Mothership.h"
#include "Game.h"

alien::alien(int x, int y, int type, Texture* textura, Mothership* mothership, PlayState* playState)
	: SceneObject(x, y, textura->getFrameWidth(), textura->getFrameHeight(), playState)
{
	this->textura = textura;
	this->mothership = mothership;
	this->type = type;
}

alien::~alien()
{
	
}

bool alien::hit(SDL_Rect other, bool fromAlien)
{
	SDL_Rect aux = SDL_Rect{ pos.getX(), pos.getY(), width, height };
	if (SDL_HasIntersection(&aux, &other) && !fromAlien)
	{
		playState->addScore(30 - (type * 10));
		mothership->alienDied();
		playState->hasDied(getAnchor(), GameObject::getAnchor());
		return true;
	}
	return false;
}

void alien::render() const
{
	SDL_Rect rectDestino{pos.getX(), pos.getY(), width, height};
	textura->renderFrame(rectDestino, type, mothership->getAlienFrame());
}

void alien::update()
{
	if (mothership->shouldMove())
	{
		if (mothership->shouldLower())
		{
			pos = pos + Point2D<int>(0, height);
		}
		else
			pos = pos + Point2D<int>(mothership->getAlienMoveDistance() * mothership->getDirection(), 0);
	}

	if ((pos + Point2D<int>(mothership->getAlienMoveDistance() * mothership->getDirection(), 0)).getX() + width >= playState->getGame()->getWidth() ||
		(pos + Point2D<int>(mothership->getAlienMoveDistance() * mothership->getDirection(), 0)).getX() <= 0)
		mothership->cannotMove();
}

void alien::save(std::ofstream& out) const
{
	out << 1 << " " << pos.getX() << " " << pos.getY() << " " << type << endl;
}