#include "Button.h"
#include "GameState.h"

Button::Button(int x, int y, Texture* textura, GameState* gameState) : GameObject(gameState)
{
	this->textura = textura;
	pos = Point2D<int>(x, y);
}
Button::~Button()
{
	
}

void Button::connect(const CallBack& callBack)
{
	this->callBack = callBack;
}

void Button::render() const
{
	SDL_Rect rectDestino{ pos.getX(), pos.getY(), 
		textura->getFrameWidth(), textura->getFrameHeight()};
	textura->renderFrame(rectDestino, 0, 0);
}

void Button::update()
{
	
}

void Button::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		hovered = (mouseX >= pos.getX() &&
			mouseX <= pos.getX() + textura->getFrameWidth() &&
			mouseY >= pos.getY() &&
			mouseY <= pos.getY() + textura->getFrameHeight());

		SDL_SetTextureColorMod(textura->getSDLTexture(), hovered ? 0 : 255, 255, hovered ? 0 : 255);
		if (event.type == SDL_MOUSEBUTTONDOWN && hovered)
		{
			callBack();
		}
	}
}