#include "laser.h"
#include "PlayState.h"
#include "alien.h"
#include "Game.h"

laser::laser(int x, int y, char color, PlayState* playState) : SceneObject(x, y, laserWidth, laserHeight, playState)
{
	Point2D<int> aux(x, y);
	pos = aux;
	this->color = static_cast<Color>(color);
}

laser::~laser()
{

}

void laser::render() const
{
	SDL_Rect rectDestino{ pos.getX(), pos.getY(), 4, 20 };
	if (color == Color::azul)
		SDL_SetRenderDrawColor(playState->getGame()->getRenderer(), 255, 0, 0, 255);
	else
		SDL_SetRenderDrawColor(playState->getGame()->getRenderer(), 0, 0, 255, 255);
	SDL_RenderFillRect(playState->getGame()->getRenderer(), &rectDestino);
}

void laser::update()
{
	Point2D<int> aux(0, 0);
	if (color == Color::azul)
		aux = aux + Point2D<int>(0, speed);
	else
		aux = aux + Point2D<int>(0, -speed);
	pos = pos + aux;

	if ((playState->damage(SDL_Rect{ pos.getX(), pos.getY(), width, height }, color == Color::azul)) || 
		(pos.getY() < 1 || pos.getY() > playState->getGame()->getHeight()))
		playState->hasDied(getAnchor(), GameObject::getAnchor());
}

bool laser::hit(SDL_Rect other, bool fromAlien)
{
	SDL_Rect aux = SDL_Rect{ pos.getX(), pos.getY(), width, height };
	if (SDL_HasIntersection(&aux, &other) && (color == Color::rojo && fromAlien))
	{
		playState->hasDied(getAnchor(), GameObject::getAnchor());
		return true;
	}
	return false;
}

void laser::save(std::ofstream& out) const
{
	out << 6 << " " << pos.getX() << " " << pos.getY() << " " << color << endl;
}