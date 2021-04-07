
#ifndef ARK2D_DEFAULTGAME_INGAMESTATE_H_
#define ARK2D_DEFAULTGAME_INGAMESTATE_H_

#include <ARK2D/Core/State/GameState.h>
#include <ARK2D/Core/Vector.h>

class DefaultGame;

class Object;
class BlankObject;
class Player;
class Pickup;
class Explosion;

class TrailItem {
	public:
		float x;
		float y;
		float t;
		float d;
};
class Particle1 {
	public:
		float time;
		float duration;
		float x;
		float y;
		float sx;
		float sy;
		float speedx;
		float speedy;
};

class InGameState : public GameState {
	public:

		Player* m_player;

		Image* sq;
		Image* cam;

		Vector3<float> simple_position;
		Vector3<float> simple_velocity;


		Vector3<float> accel_position;
		Vector3<float> accel_velocity;
		float accel_velocityMax;
		Vector3<float> accel_acceleration;

		Vector3<float> jump_position;
		Vector3<float> jump_velocity;
		float jump_jumpvelocity;
		float jump_gravity;
		float jumpLineY;
		float jump_timer;
		float jump_duration;
		float jump_landtimer;
		float jump_landduration;
		bool jump_grounded;
		float jump_stretch;
		float jump_squash;

		float camera_timer;
		float camera_duration;
		int camera_state;

		float easings_timer;
		float easings_duration;
		int easings_state;

		vector<TrailItem*> trails;

		Image* enemybob;
		float enemybobtimer;
		float enemybobduration;
		Image* playerbob;
		float m_walkWobbleTimer;
		float m_walkWobbleDuration;
		float m_walkWobbleMaxRotation;

		Animation* bird;
		Animation* explosion;
		float bird_explode_timer;
		float bird_explode_duration;

		Image* particletile;
		Animation* particlefx1;
		float particleSpawnTimer;
		float particleSpawnDuration;
		vector<float> particleSpawnXs;
		int particleSpawnXIndex;
		vector<Particle1*> particle1s;
		float p1x1;
		float p1x2;

		float particle2SpawnTimer;
		float particle2SpawnDuration;

		int scenario;
		static const unsigned int SCENARIO_SIMPLE = 0;
		static const unsigned int SCENARIO_ACCEL = 1;
		static const unsigned int SCENARIO_MICRO = 2;
		static const unsigned int SCENARIO_JUMP = 3;
		static const unsigned int SCENARIO_CAMERATWEENS = 4;
		static const unsigned int SCENARIO_EASINGS = 5;
		static const unsigned int SCENARIO_MOVEMENTS = 6;
		static const unsigned int SCENARIO_CONTINUITY = 7;
		static const unsigned int SCENARIO_PARTICLES1 = 8;
		static const unsigned int SCENARIO_PARTICLES2 = 9;
		static const unsigned int SCENARIO_PARTICLES3 = 10;

		// 0 - simple
		// 1 - accel
		// 2 -- missing
		// 3 - particles


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
