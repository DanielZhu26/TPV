#include "bunker.h"
#include "PlayState.h"

bunker::bunker(int x, int y, int currentHits, Texture* textura, PlayState* playState) :
	SceneObject(x, y, textura->getFrameWidth(), textura->getFrameHeight(), playState)
{
	hits = currentHits;
	this->textura = textura;
}

bunker::~bunker()
{

}

void bunker::render() const
{
	SDL_Rect rectDestino {pos.getX(), pos.getY(), width, height};
	textura->renderFrame(rectDestino, 0, hits);
}

void bunker::update()
{

}

void bunker::save(std::ofstream& out) const
{
	out << 4 << " " << pos.getX() << " " << pos.getY() << " " << (4 + hits) << endl;
}

bool bunker::hit(SDL_Rect other, bool fromAlien)
{
	SDL_Rect aux = { pos.getX(), pos.getY(), width, height };
	if (SDL_HasIntersection(&other, &aux))
	{
		if ((hits + 1) >= maxHits)
			playState->hasDied(getAnchor(), GameObject::getAnchor());
		else
			hits++;
		return true;
	}
	return false;
}