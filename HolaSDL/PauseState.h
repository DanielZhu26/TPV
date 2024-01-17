#ifndef PAUSESTATE_H
#define PAUSESTATE_H
#include "../checkML.h"
#include "GameState.h"
#include "Button.h"
#include "EventHandler.h"

class Game;
class PlayState;
class MainMenuState;

class PauseState : public GameState
{
private:
	PlayState* playState;

	bool loading;
	bool saving;
	int code = -1;
public:
	PauseState(Game* game, PlayState* playState);

	void render() const override;

	void addNumber(int number);
	void removeNumber();

	class PauseEventHandler : public EventHandler
	{
	private:
		PauseState* pauseState;
	public:
		PauseEventHandler(PauseState* pauseState) {
			this->pauseState = pauseState; }

		void handleEvent(SDL_Event& event) override;
	};
};
#endif