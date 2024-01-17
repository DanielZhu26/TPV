#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H
#include <stack>
#include "GameState.h"
#include "../checkML.h"

using namespace std;
class GameStateMachine
{
private:
	stack<GameState*> states;
	SDL_Event event;

	// para poder cambiar de state después del handleevent para evitar
	// codigo imprevisible al hacer delete del state
	bool pendingReplace = false;
	bool pendingPop = false;
	bool doublePendingPop = false;
	GameState* pendingState = nullptr;
public:
	GameStateMachine(GameState* startingState);

	void pushState(GameState* newState);

	void replaceState(GameState* newState);

	void popState();

	void doblePopReplace(GameState* newState);

	void vaciarStates();

	void update();

	void render() const;

	void handleEvent();

	bool isEmpty() { return states.empty(); }
};
#endif