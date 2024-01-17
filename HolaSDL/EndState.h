#ifndef ENDSTATE_H
#define ENDSTATE_H
#include "../checkML.h"
#include "GameState.h"
#include "Button.h"
#include "MainMenuState.h"
#
class Game;

class EndState : public GameState
{
private:

public:
	EndState(Game* game);

	void render() const override;

	void update() override;

	class EndEventHandler : public EventHandler
	{
	private:
		EndState* endState;
	public:
		EndEventHandler(EndState* endState) {
			this->endState = endState;
		}

		void handleEvent(SDL_Event& event) override;
	};
};
#endif