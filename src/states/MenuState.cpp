
#include "MenuState.h"
#include "../DefaultGame.h"
#include <ARK2D/Core/Font/FTFont.h>

MenuState::MenuState():
	GameState() {

}

unsigned int MenuState::id() {
	return StatesList::STATE_MENU;
}

void MenuState::enter(GameContainer* container, StateBasedGame* game, GameState* from) {

}

void MenuState::leave(GameContainer* container, StateBasedGame* game, GameState* to) {

}

void MenuState::init(GameContainer* container, StateBasedGame* game) {
	DefaultGame* dg = DefaultGame::getInstance();
	m_selectedIndex = 0;

	//ARK2D::getRenderer()->getDefaultFont()->style.outlineThickness = 1;
	ARK2D::getRenderer()->getDefaultFont()->style.shadowX = ARK2D::getRenderer()->getDefaultFont()->style.shadowY = 1;

	Renderer::setInterpolation(Renderer::INTERPOLATION_LINEAR);
	ftfont = new ARK::Core::Font::FTFont("Arial Unicode.ttf", 24);
	ftfont->style.outlineThickness = 2;
	ftfont_jp = new ARK::Core::Font::FTFont("corp_round_v1_jp.ttf", 24);
	ftfont_ko = new ARK::Core::Font::FTFont("BMJUA_ttf_ko.ttf", 24);
    //ftfont = new ARK::Core::Font::FTFont("Arial.ttf", 24);

    Renderer::setInterpolation(Renderer::INTERPOLATION_NEAREST);
}

void MenuState::update(GameContainer* container, StateBasedGame* game, GameTimer* timer) {
	DefaultGame* dg = DefaultGame::getInstance();
	Input* i = ARK2D::getInput();

	if (i->isKeyPressed(Input::KEY_W) ||
		i->isKeyPressed(Input::KEY_UP) ||
		i->isGamepadButtonPressed(Gamepad::DPAD_UP)) {
		m_selectedIndex--;
		if (m_selectedIndex < MENU_BEGIN) {
			m_selectedIndex = MENU_END;
		}
	}
	if (i->isKeyPressed(Input::KEY_S) ||
		i->isKeyPressed(Input::KEY_DOWN) ||
		i->isGamepadButtonPressed(Gamepad::DPAD_DOWN)) {
		m_selectedIndex++;
		if (m_selectedIndex > MENU_END) {
			m_selectedIndex = MENU_BEGIN;
		}
	}


	if (i->isKeyPressed(Input::KEY_ENTER) ||
		i->isGamepadButtonPressed(Gamepad::BUTTON_START) ||
		i->isGamepadButtonPressed(Gamepad::BUTTON_A)) {
		if (m_selectedIndex == MENU_PLAY) {
			dg->stateInGame->reset();
			dg->stateInGame->start();
			game->enterState(dg->stateInGame);

		}
		else if (m_selectedIndex == MENU_INSTRUCTIONS) {
			game->enterState(dg->stateInstructions);
		}
		else if (m_selectedIndex == MENU_EXIT) {
			container->close();
		}
	}
}

void MenuState::render(GameContainer* container, StateBasedGame* game, Renderer* r) {
	DefaultGame* dg = DefaultGame::getInstance();
	InGameState* igs = dg->stateInGame;
	r->drawString("Menu", 20, 20, Renderer::ALIGN_LEFT, Renderer::ALIGN_TOP);

	r->setDrawColor(Color::blue);
	r->fillRect(0,0,container->getWidth(), container->getHeight());
	r->setDrawColor(Color::white);
    //r->getFont()->drawString("hi 今日のスペシャル：マフィン！ わーい！yo", 20, 40);
    r->getFont()->drawString("hi yo", 20, 60);
    r->getFont()->drawString(StringUtil::append("lh: ", ftfont->getLineHeight()), 20, 80);

    r->setDrawColor(Color::blue);
    r->drawLine(20,100,120,100);
    r->drawLine(20,124,120,124);
    //r->drawLine(20,120,120,120);

    r->setDrawColor(Color::white);
    //ftfont->drawString("hi, yo 2!", 20, 100);
    // Japanese
    // G7 Cute Pop Bold
    // idfont FTMaru (あいでぃーぽっぷふとまる)
    // Corporate Font Rounded.
    // mini-wakuwaku
    // ..
    // Korean
    // BM JUA

    ftfont->drawStringCenteredAt(string("HEY YA! (hello world)!"), container->getWidth()*0.5f, 100);

    //ftfont->drawString(string("hi 今日のスペシャル：マフィン！ わーい！yo"), 20, 100);
    //ftfont_jp->drawString(string("hi 今日のスペシャル：マフィン！ わーい！yo"), 20, 140);
    //ftfont_ko->drawString(string("장식하는 두손을 실현에 부패를 수 때문이다."), 20, 180);

	//ftfont->drawStringCenteredAt(string("hi 今日のスペシャル：マフィン！ わーい！yo"), container->getWidth()*0.5f, 100);
    ftfont_jp->drawStringCenteredAt(string("読み込んでいます..."), container->getWidth()*0.5f, 140);
    ftfont_jp->drawStringCenteredAt(string("すべてのロックを解除"), container->getWidth()*0.5f, 180);

    ftfont_jp->getStringWidth("すべてのロックを解除");

    //ftfont_ko->drawStringCenteredAt(string("장식하는 두손을 실현에 부패를 수 때문이다."), container->getWidth()*0.5f, 180);
    //ftfont_ko->drawStringFitWidth(string("장식하는 두손을 실현에 부패를 수 때문이다."), container->getWidth()*0.5f, 230, Renderer::ALIGN_CENTER, Renderer::ALIGN_CENTER, 0.0f, 1.0f, 250);

	int rooty = 320;
	int wid = (signed int) container->getWidth();

    //r->texturedRect(ftfont->m_data->texture, 200,200, ftfont->m_data->textureWidth,ftfont->m_data->textureHeight);

 //    r->setDrawColor(Color::red);
 //    r->drawRect(200,200, ftfont->m_data->textureWidth,ftfont->m_data->textureHeight);
     r->setDrawColor(Color::white);

	if (m_selectedIndex == MENU_PLAY) {
		r->getFont()->drawStringCenteredAt("< Play >", wid/2, rooty);
	}
	else {
		r->getFont()->drawStringCenteredAt("Play", wid/2, rooty);
	}

	if (m_selectedIndex == MENU_INSTRUCTIONS) {
		r->getFont()->drawStringCenteredAt("< Instructions >", wid/2, rooty+40);
	}
	else {
		r->getFont()->drawStringCenteredAt("Instructions", wid/2, rooty+40);
	}

	if (m_selectedIndex == MENU_EXIT) {
		r->getFont()->drawStringCenteredAt("< Exit >", wid/2, rooty+80);
	}
	else {
		r->getFont()->drawStringCenteredAt("Exit", wid/2, rooty+80);
	}
}

MenuState::~MenuState() {

}
