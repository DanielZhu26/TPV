#include "Reward.h"
#include "cannon.h"
#include "PlayState.h"
#include "Game.h"

Reward::Reward(int x, int y, Texture* textura, cannon* player, PlayState* playState) 
	: SceneObject(x, y, textura->getFrameWidth(), textura->getFrameHeight(), playState)
{
	this->textura = textura;
	this->player = player;
}

Reward::~Reward()
{
}

void Reward::render() const
{
	SDL_Rect rectDestino{ pos.getX(), pos.getY(), width, height };
	textura->renderFrame(rectDestino, 0, 0);
}

void Reward::update()
{
	pos = pos + Point2D<int>(0, 1);
	if ((pos - Point2D<int>(0, 1)).getY() > playState->getGame()->getHeight() + height)
		delete this;
	else
	{
		SDL_Rect aux = SDL_Rect{ pos.getX(), pos.getY(), width, height };
		if (SDL_HasIntersection(&aux, &player->getRect()))
		{
			callBack();
			playState->hasDied(getAnchor(), GameObject::getAnchor());
			delete this;
		}
	}
}

void Reward::connect(const CallBack& callBack)
{
	this->callBack = callBack;
}