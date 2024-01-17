#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(GameState* startingState)
{
	states.push(startingState);
}

void GameStateMachine::pushState(GameState* newState)
{
	pendingState = newState;
}

void GameStateMachine::replaceState(GameState* newState)
{
	pendingReplace = true;
	pendingState = newState;
}

void GameStateMachine::popState()
{
	pendingPop = true;
}

void GameStateMachine::doblePopReplace(GameState* newState)
{
	pendingPop = true;
	doublePendingPop = true;
	pendingState = newState;
}

void GameStateMachine::update()
{
	states.top()->update();
}

void GameStateMachine::render() const
{
	states.top()->render();
}

void GameStateMachine::vaciarStates()
{
	while (!states.empty())
	{
		states.pop();
	}
}

void GameStateMachine::handleEvent()
{
	if (SDL_PollEvent(&event))
		states.top()->handleEvent(event);

	if (pendingPop || pendingState != nullptr)
	{
		if (pendingReplace || pendingPop)
		{
			GameState* stateToDelete = states.top();
			states.pop();
			stateToDelete->clearEventHandler();
			delete stateToDelete;
			if (doublePendingPop)
			{
				GameState* stateToDelete = states.top();
				states.pop();
				stateToDelete->clearEventHandler();
				delete stateToDelete;
				doublePendingPop = false;
			}
		}
		if (pendingReplace || pendingState != nullptr)
			states.push(pendingState);

		pendingPop = false;
		pendingReplace = false;
		pendingState = nullptr;
	}
}