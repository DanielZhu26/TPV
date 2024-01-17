#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "../checkML.h"
#include "GameState.h"
#include "EventHandler.h"
#include "Button.h"
#include "PlayState.h"
#include <string>

class Game;

class MainMenuState : public GameState
{
private:
	bool loading = false;
	bool pendingEventHandlerChange = false;
	int loadCode = -1;
public:
	MainMenuState(Game* game);

	~MainMenuState();

	void render() const override;

	void update() override;

	void LoadGame();

	void addNumber(int number);
	void removeNumber();
	int getLoadCode() { return loadCode; }

	class LoadGameEventHandler : public EventHandler
	{
	private:
		MainMenuState* mainMenuState;
	public:
		LoadGameEventHandler(MainMenuState* mainMenuState) {
			this->mainMenuState = mainMenuState; }

		void handleEvent(SDL_Event& event) override;
	};

	class MainMenuEventHandler : public EventHandler
	{
	private:
		MainMenuState* mainMenuState;
	public:
		MainMenuEventHandler(MainMenuState* mainMenuState) {
			this->mainMenuState = mainMenuState; }

		void handleEvent(SDL_Event& event) override;
	};
};
#endif