#ifndef REWARD_H
#define REWARD_H
#include "../checkML.h"
#include "SceneObject.h"
#include "texture.h"
#include <functional>

class cannon;
class PlayState;
class Game;

using CallBack = std::function<void(void)>;

class Reward : public SceneObject
{
protected:
	Texture* textura;
	cannon* player;
	CallBack callBack;
public:
	Reward(int x, int y, Texture* textura, cannon* player, PlayState* playState);

	~Reward();

	void render() const override;

	virtual	void update() override;

	void save(std::ofstream& out) const override {}

	bool hit(SDL_Rect other, bool fromAlien) override { return false; }

	void connect(const CallBack& callBack);
};
#endif