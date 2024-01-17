#ifndef INFOBAR_H
#define INFOBAR_H
#include "../checkML.h"
#include "GameObject.h"
#include "texture.h"

class PlayState;
class Game;

class InfoBar : public GameObject
{
protected:
	Texture* texturaCannon;
	Texture* texturaNumeros;
	Uint64 score;
	PlayState* playState;
public:

	InfoBar(int score, Texture* texturaCannon, Texture* texturaNumeros, PlayState* playState);

	~InfoBar();

	void render() const override;

	void update() override;

	void save(std::ofstream& out) const;

	void addScore(int newScore) { score += newScore; }

	Uint64 getScore() { return score; }
};
#endif

