#ifndef BUTTON_H
#define BUTTON_H
#include "../checkML.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "Vector2D.h"
#include <functional>
#include "texture.h"


using CallBack = std::function<void(void)>;

class Button : public GameObject, public EventHandler
{
private:
	Point2D<int> pos;
	Texture* textura;
	CallBack callBack;

	bool hovered = false;
public:
	Button(int x, int y, Texture* textura, GameState* gameState);

	~Button();

	void render() const override;

	void update() override;

	void save(std::ofstream& out) const override {};

	void connect(const CallBack& callBack);

	void handleEvent(SDL_Event& event) override;
};
#endif