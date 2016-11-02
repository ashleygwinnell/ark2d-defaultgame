
#ifndef ARK2D_DEFAULTGAME_INGAMESTATE_H_
#define ARK2D_DEFAULTGAME_INGAMESTATE_H_

#include <ARK2D/Core/State/GameState.h>

class DefaultGame;

class Object;
class BlankObject;
class Player;
class Pickup;
class Explosion;

class InGameState : public GameState {
	public:

		Player* m_player;

		InGameState();
		void enter(GameContainer* container, StateBasedGame* game, GameState* from);
		void leave(GameContainer* container, StateBasedGame* game, GameState* to);

		unsigned int id();
		void reset();
		void start();
		void init(GameContainer* container, StateBasedGame* game);
		void update(GameContainer* container, StateBasedGame* game, GameTimer* timer);
		void render(GameContainer* container, StateBasedGame* game, Renderer* r);

		virtual ~InGameState();
};

#endif /* ARK2D_DEFAULTGAME_INGAMESTATE_H_ */
