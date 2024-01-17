#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include "../checkML.h"
#include "GameState.h"
#include "customExceptions.h"
#include "EventHandler.h"
#include "texture.h"
#include "Mothership.h"
#include "cannon.h"
#include "laser.h"
#include "alien.h"
#include "shooterAlien.h"
#include "bunker.h"
#include "ufo.h"
#include "InfoBar.h"
#include "PauseState.h"
#include "Reward.h"

using namespace std;
using uint = unsigned int;

class Game;

class PlayState : public GameState
{
private:
	GameList<SceneObject, false> sceneObjects;
	Mothership* mothership;
	cannon* player;
	InfoBar* infoBar;
public:
	PlayState(Game* game, string filename, int score);

	~PlayState();

	void render() const override;

	void update() override;

	void hasDied(GameList<SceneObject, false>::anchor anchor, GameList<GameObject, true>::anchor anchor2);

	bool damage(SDL_Rect damageZone, bool fromAlien);

	void fireLaser(Point2D<int> pos, char color);

	void addScore(int score);

	void saveGame(string filename);

	void loadScene(string filename);

	void mayGrantReward(int x, int y);

	int getPlayerLives() { return player->GetLives(); }

	int getScore() { return infoBar->getScore(); }

	class Bomb : public Reward
	{
	private: 
		int lives = 2;
	public:
		Bomb(int x, int y, Texture* textura, cannon* player, PlayState* playState);
		
		void update() override;
	};

	class Shield : public Reward
	{
	private:
		int shieldTime = 6000;
	public:
		Shield(int x, int y, Texture* textura, cannon* player, PlayState* playState);
	};

	class PlayStateEventHandler : public EventHandler
	{
	private:
		PlayState* playState;
	public:
		PlayStateEventHandler(PlayState* playState) {
			this->playState = playState;
		}

		void handleEvent(SDL_Event& event) override;
	};
};
#endif