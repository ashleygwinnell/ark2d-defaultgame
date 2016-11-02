
#include "InGameState.h"
#include "../DefaultGame.h"

InGameState::InGameState():
	GameState()
	{

}

unsigned int InGameState::id() {
	return StatesList::STATE_INGAME;
}

void InGameState::enter(GameContainer* container, StateBasedGame* game, GameState* from) {

}

void InGameState::leave(GameContainer* container, StateBasedGame* game, GameState* to) {

}

void InGameState::init(GameContainer* container, StateBasedGame* game) {
	start();
}

void InGameState::reset() {

}

void InGameState::start() {
	reset();
}

void InGameState::update(GameContainer* container, StateBasedGame* game, GameTimer* timer) {
	DefaultGame* dg = DefaultGame::getInstance();
	Input* in = ARK2D::getInput();

	if (in->isKeyPressed(Input::KEY_ESCAPE) ||
		in->isKeyPressed(Input::KEY_ENTER) ||
		in->isKeyPressed(Input::KEY_BACKSPACE) ||
		in->isGamepadButtonPressed(Gamepad::BUTTON_START)) {
		game->enterState(dg->stateMenu);
	}

}

void InGameState::render(GameContainer* container, StateBasedGame* game, Renderer* r) {
	r->setDrawColor(Color::white);
	r->drawString("In Game State", 20, 20);
}

InGameState::~InGameState() {

}

