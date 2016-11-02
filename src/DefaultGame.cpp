
#include "DefaultGame.h"

DefaultGame::DefaultGame(string title):
	StateBasedGame(title) {

}

void DefaultGame::initStates(GameContainer* container) {

	stateBlank = new BlankState();
	stateSplash = new SplashState();
	stateMenu = new MenuState();
	stateInstructions = new InstructionsState();
	stateInGame = new InGameState();
	stateSummary = new SummaryState();

	addState(stateBlank);
	addState(stateSplash);
	addState(stateMenu);
	addState(stateInstructions);
	addState(stateInGame);
	addState(stateSummary);

	enterState(stateMenu);
}

void DefaultGame::update(GameContainer* container, GameTimer* timer) {
	StateBasedGame::update(container, timer);

	Input* i = ARK2D::getInput();
	if (i->isGamepadButtonPressed(Gamepad::BUTTON_ACTIVATE) || i->isKeyPressed(Input::KEY_F)) {
		container->setFullscreen(!container->isFullscreen());
	}
}

void DefaultGame::render(GameContainer* container, Renderer* r) {
	StateBasedGame::render(container, r);
}

void DefaultGame::resize(GameContainer* container, int width, int height) {
	StateBasedGame::resize(container, width, height);
}

DefaultGame* DefaultGame::getInstance() {
    return dynamic_cast<DefaultGame*>(ARK2D::getGame());
}

DefaultGame::~DefaultGame() {

}
