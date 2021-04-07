
#include "InGameState.h"
#include "../DefaultGame.h"

#include <ARK2D/Core/Graphics/Animation.h>
#include <ARK2D/Core/Tween/Easing.h>

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

	sq = Resource::get("100x100.png")->asImage();
	cam = Resource::get("camera-icon.png")->asImage();

	simple_position.set(container->getWidth()*0.33f, container->getHeight() * 0.5f, 0);
	simple_velocity.set(150, 150, 150);


	accel_position.set(container->getWidth()*0.66f, container->getHeight() * 0.5f, 0);
	accel_velocity.set(0, 0, 0);
	accel_velocityMax = 150;
	accel_acceleration.set(2000, 2000, 2000);

	jump_position.set(container->getWidth()*0.33f, container->getHeight() * 0.5f, 0);
	jump_velocity.set(0,0,0);
	jump_jumpvelocity = 700;
	jump_gravity = 2500;
	jumpLineY = container->getHeight() * 0.75f;
	jump_timer = 0.0f;
	jump_duration = 0.6f;
	jump_landtimer = 0.0f;
	jump_landduration = 0.35f;
	jump_grounded = false;
	jump_stretch = 1.9f;
	jump_squash = 0.6f;

	camera_timer = 0.0f;
	camera_duration = 1.5f;
	camera_state = 0;

	easings_timer = 0.01f;
	easings_duration = 5.0f;
	easings_state = 0;

	enemybob = Resource::get("enemy-medium.png")->asImage();
	enemybobtimer = 0.0f;
	enemybobduration = 0.35f;
	playerbob = Resource::get("player-front-1.png")->asImage();
	playerbob->scale(5.0f, 5.0f);
	playerbob->setCenterOfRotation(playerbob->getWidth()/2, playerbob->getHeight());

	m_walkWobbleTimer = 0.0f;
	m_walkWobbleDuration = 0.35f;
	m_walkWobbleMaxRotation = 4.0f;

	//bird = AnimationFrameList::create("crow/crow*.png", 0, 5, NULL, NULL, 2);
	//explosion = AnimationFrameList::create("crow/explosion2-*.png", 0, 19, NULL, NULL, 2);
	bird = new Animation();
	bird->addFrame( Resource::get("crow/crow00.png")->asImage() );
	bird->addFrame( Resource::get("crow/crow01.png")->asImage() );
	bird->addFrame( Resource::get("crow/crow02.png")->asImage() );
	bird->addFrame( Resource::get("crow/crow03.png")->asImage() );
	bird->addFrame( Resource::get("crow/crow04.png")->asImage() );
	bird->addFrame( Resource::get("crow/crow05.png")->asImage() );
	bird->setFrameTime(0.1f);

	explosion = new Animation();
	explosion->addFrame( Resource::get("crow/explosion2-00.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-01.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-02.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-03.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-04.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-05.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-06.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-07.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-08.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-09.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-10.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-11.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-12.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-13.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-14.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-15.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-16.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-17.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-18.png")->asImage() );
	explosion->addFrame( Resource::get("crow/explosion2-19.png")->asImage() );
	explosion->setFrameTime(0.1f);

	bird_explode_timer = 0.0f;
	bird_explode_duration = 3.0f;

	particletile = Resource::get("17x17.png")->asImage();
	particletile->scale(2.0f, 2.0f);
	particlefx1 = new Animation();
	particlefx1->addFrame( Resource::get("fx/cloud-3x3-1.png")->asImage() );
	particlefx1->addFrame( Resource::get("fx/cloud-3x3-2.png")->asImage() );
	particlefx1->addFrame( Resource::get("fx/cloud-3x3-3.png")->asImage() );
	particlefx1->addFrame( Resource::get("fx/cloud-3x3-4.png")->asImage() );
	particlefx1->addFrame( Resource::get("fx/cloud-3x3-5.png")->asImage() );
	particlefx1->setFrameTime(0.2f);
	particleSpawnTimer = 0.0f;
	particleSpawnDuration = 0.1f;
	particleSpawnXs.push_back(0.5f);
	particleSpawnXs.push_back(0.25f);
	particleSpawnXs.push_back(0.75f);
	particleSpawnXs.push_back(0.0f);
	particleSpawnXs.push_back(1.0f);
	particleSpawnXs.push_back(0.5f);
	particleSpawnXs.push_back(0.33f);
	particleSpawnXs.push_back(0.66f);
	particleSpawnXs.push_back(0.15f);
	particleSpawnXs.push_back(0.85f);
	particleSpawnXIndex = 0;

	p1x1 = container->getWidth() * 0.4f;
	p1x2 = container->getWidth() * 0.6f;

	particle2SpawnDuration = 2.0f;
	particle2SpawnTimer = particle2SpawnDuration;

	//Vector<float> trailXs;
	//Vector<float> trailYs;

	//scenario = SCENARIO_JUMP;
	//scenario = SCENARIO_CAMERATWEENS;
	//scenario = SCENARIO_EASINGS;
	//scenario = SCENARIO_MOVEMENTS;
	//scenario = SCENARIO_CONTINUITY;
	//scenario = SCENARIO_PARTICLES1;
	//scenario = SCENARIO_PARTICLES2;
	scenario = SCENARIO_PARTICLES3;

	//if (scenario == SCENARIO_CAMERATWEENS || scenario == SCENARIO_EASINGS) {
		container->setSize(640*2, 480*2);
	//}

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
    float delta = timer->getDelta();

	// simple
	if (in->isKeyDown(Input::KEY_LEFT)) {
        simple_position.x -= simple_velocity.x * delta;
    } else if (in->isKeyDown(Input::KEY_RIGHT)) {
        simple_position.x += simple_velocity.x * delta;
    }
    if (in->isKeyDown(Input::KEY_UP)) {
        simple_position.y -= simple_velocity.y * delta;
    } else if (in->isKeyDown(Input::KEY_DOWN)) {
        simple_position.y += simple_velocity.y * delta;
    }

	// accel
    if (in->isKeyDown(Input::KEY_LEFT)) {
        accel_velocity.x -= accel_acceleration.x * delta;
    } else if (in->isKeyDown(Input::KEY_RIGHT)) {
        accel_velocity.x += accel_acceleration.x * delta;
    } else {
    	accel_velocity.frictionX(accel_acceleration.x * delta);
    }
    if (in->isKeyDown(Input::KEY_UP)) {
        accel_velocity.y -= accel_acceleration.y * delta;
    } else if (in->isKeyDown(Input::KEY_DOWN)) {
        accel_velocity.y += accel_acceleration.y * delta;
    } else {
        accel_velocity.frictionY(accel_acceleration.y * delta);
    }
    accel_velocity.clamp(accel_velocityMax);
    accel_position += accel_velocity * delta;

    if (scenario == SCENARIO_SIMPLE) {
		TrailItem* ti = new TrailItem();
		ti->x = simple_position.x;
		ti->y = simple_position.y;
		ti->t = 0.0f;
		  ti->d = 1.0f;
		trails.push_back(ti);
	}
	if (scenario == SCENARIO_ACCEL) {
	    TrailItem* ti2 = new TrailItem();
	    ti2->x = accel_position.x;
	    ti2->y = accel_position.y;
	    ti2->t = 0.0f;
	   	ti2->d = 1.0f;
	    trails.push_back(ti2);
	}
	if (scenario == SCENARIO_JUMP) {
		if (in->isKeyPressed(Input::KEY_SPACE) || in->isKeyPressed(Input::KEY_UP)) {
			jump_timer = 0.01f;
			jump_velocity.set(0, jump_jumpvelocity * -1, 0);
			jump_grounded = false;
		}

		if (jump_timer > 0.0f) {
			jump_timer += timer->getDelta();
			if (jump_timer >= jump_duration) {
				jump_timer = 0.0f;
			}
		}
		if (jump_landtimer > 0.0f) {
			jump_landtimer += timer->getDelta();
			if (jump_landtimer >= jump_landduration) {
				jump_landtimer = 0.0f;
			}
		}

		jump_velocity.y += jump_gravity * delta;
		jump_velocity.clamp(jump_jumpvelocity);
		jump_position += jump_velocity * delta;;
		if (jump_position.y > jumpLineY) {
			jump_position.y = jumpLineY;

			if (jump_landtimer == 0.0f && !jump_grounded) {
				jump_landtimer = 0.01f;
			}
			jump_grounded = true;
		}

	}

	if (scenario == SCENARIO_CAMERATWEENS) {
		if (in->isKeyPressed(Input::KEY_SPACE)) {
			camera_timer = 0.01f;
		}

		if (camera_timer > 0.0f) {
			camera_timer += timer->getDelta();
			if (camera_timer >= camera_duration) {
				camera_timer = 0.0f;
				camera_state = (camera_state == 0)?1:0;
			}
		}
	}
	if (scenario == SCENARIO_EASINGS) {
		easings_timer += delta;
		if (easings_timer > 0.0f) {
			easings_timer += timer->getDelta();
			if (easings_timer >= easings_duration) {
				easings_timer = 0.01f;
				easings_state = (easings_state == 0)?1:0;
			}
		}
	}
	if (scenario == SCENARIO_MOVEMENTS) {
		enemybobtimer += timer->getDelta();
		if (enemybobtimer >= enemybobduration) {
			enemybobtimer -= enemybobduration;
		}

		m_walkWobbleTimer += timer->getDelta();
		if (m_walkWobbleTimer >= m_walkWobbleDuration) {
			m_walkWobbleTimer -= m_walkWobbleDuration;
		}
	}
	if (scenario == SCENARIO_CONTINUITY) {
		bird->update(delta);

		if (bird_explode_timer > 0.0f) {
			bird_explode_timer += delta;
			if (bird_explode_timer >= bird_explode_duration) {
				bird_explode_timer = 0.0f;
			}

			signed int i = explosion->getCurrentFrameIndex();
			explosion->update(delta);
			if (explosion->getCurrentFrameIndex() < i) {
				bird_explode_timer = 0.0f;
			}
		}

		if (in->isKeyPressed(Input::KEY_SPACE) || in->isKeyPressed(Input::KEY_UP)) {
			bird_explode_timer = 0.01f;
			explosion->setTime(0.0f);
		}
	}
	if (scenario == SCENARIO_PARTICLES1) {
		particleSpawnTimer += delta;
		if (particleSpawnTimer >= particleSpawnDuration) {
			particleSpawnTimer -= particleSpawnDuration;

			// container->getWidth()*0.4f, container->getHeight() * 0.5f
			float w = 22.0f;
			float speedy = -1.5f;
			float diffMin = 0.75f;
			float diffMax = 1.25f;

			Particle1* p1 = new Particle1();;
			p1->time = 0.0f;
			p1->duration = (float) (particlefx1->getFrameTime() * particlefx1->size() * MathUtil::randBetweenf(diffMin, diffMax));
			p1->x = (p1x1) - (w*0.5f) + (w*MathUtil::randBetweenf(0.0f, 1.0f));
			p1->y = (container->getHeight()*0.5f);
			p1->speedx = 0;
			p1->speedy = speedy;
            particle1s.push_back(p1);

            float r = particleSpawnXs.at(particleSpawnXIndex);

            Particle1* p2 = new Particle1();;
			p2->time = 0.0f;
			p2->duration = (float) (particlefx1->getFrameTime() * particlefx1->size() * MathUtil::randBetweenf(diffMin, diffMax));
			p2->x = (p1x2) - (w*0.5f) + (w*r);
			p2->y = (container->getHeight()*0.5f);
			p2->speedx = 0;
			p2->speedy = speedy;
            particle1s.push_back(p2);

            particleSpawnXIndex = (particleSpawnXIndex + 1) % particleSpawnXs.size();;

		}
	}

	if (scenario == SCENARIO_PARTICLES2 || scenario == SCENARIO_PARTICLES3) {
		particle2SpawnTimer += delta;
		if (particle2SpawnTimer >= particle2SpawnDuration) {
			particle2SpawnTimer -= particle2SpawnDuration;

			// container->getWidth()*0.4f, container->getHeight() * 0.5f
			float w = 22.0f;
			float speedy = 1.0f;
			float diffMin = 0.8f;
			float diffMax = 0.8f;

			for (int i = 0; i < 8; i++) {
				float oneAngle = MathUtil::randBetweenf(0.0f, 360.0f);
				Particle1* p1 = new Particle1();
				p1->time = 0.0f;
				p1->duration = (float) (particlefx1->getFrameTime() * particlefx1->size() * MathUtil::randBetweenf(diffMin, diffMax));
				p1->sx = p1->x = (p1x1);
				p1->sy = p1->y = (container->getHeight()*0.5f);
				p1->speedx = 0;
				p1->speedy = 0;
				MathUtil::moveAngle<float>(p1->speedx, p1->speedy, oneAngle, speedy);
	            particle1s.push_back(p1);

	            float twoAngle = (float(i) * 45.0f) - 15 + MathUtil::randBetweenf(0.0f, 30.0f);
	            Particle1* p2 = new Particle1();;
				p2->time = 0.0f;
				p2->duration = (float) (particlefx1->getFrameTime() * particlefx1->size() * MathUtil::randBetweenf(diffMin, diffMax));
				p2->sx = p2->x = (p1x2);
				p2->sy = p2->y = (container->getHeight()*0.5f);
				p2->speedx = 0;
				p2->speedy = 0;
				MathUtil::moveAngle<float>(p2->speedx, p2->speedy, twoAngle, speedy);
	            particle1s.push_back(p2);
			}
		}
	}

	if (scenario == SCENARIO_PARTICLES1 || scenario == SCENARIO_PARTICLES2) {
		for(int i = 0; i < particle1s.size(); i++) {
			Particle1* p1 = particle1s[i];
			p1->time += delta;
			p1->x += p1->speedx;
			p1->y += p1->speedy;
			if (p1->time >= p1->duration) {
				particle1s.erase(particle1s.begin() + i);
				i--;
				delete p1;
			}
		}
	}
	if (scenario == SCENARIO_PARTICLES3) {
		for(int i = 0; i < particle1s.size(); i++) {
			Particle1* p1 = particle1s[i];
			p1->time += delta;
			float an = MathUtil::anglef(0,0, p1->speedx ,p1->speedy);
			float dis = 40.0f; //MathUtil::distance(0,0,p1->speedx ,p1->speedy);
			float ex = p1->sx;
			float ey = p1->sy;
			MathUtil::moveAngle<float>(ex, ey, an, dis);
			p1->x = Easing::easebetween(Easing::QUADRATIC_OUT, p1->time, p1->sx, ex, p1->duration);
			p1->y = Easing::easebetween(Easing::QUADRATIC_OUT, p1->time, p1->sy, ey, p1->duration);
			if (p1->time >= p1->duration) {
				particle1s.erase(particle1s.begin() + i);
				i--;
				delete p1;
			}
		}
	}

    for(int i = 0; i < trails.size(); i++) {
    	trails[i]->t += delta;
    	if (trails[i]->t >= trails[i]->d) {
            TrailItem* ti = trails[i];
    		trails.erase(trails.begin() + i);
    		i--;
    		delete ti;
    	}
    }
}

void InGameState::render(GameContainer* container, StateBasedGame* game, Renderer* r) {

	// r->drawString("In Game State", 20, 20);

    r->setDrawColor("#161616");
    r->fillRect(0,0,container->getWidth(), container->getHeight());

	r->setDrawColor(Color::white_50a);
	r->setDrawColor(Color::white);
	for (int i = 0; i < trails.size(); i++) {
		r->fillCircle(trails[i]->x, trails[i]->y, 2, 10);
	}

	r->setDrawColor(Color::white);
	if (scenario == SCENARIO_SIMPLE) {
		sq->draw(container->getWidth()*0.33f, container->getHeight() * 0.5f);
		r->fillCircle(simple_position.x, simple_position.y, 15, 30);
	}
	else if (scenario == SCENARIO_SIMPLE) {
		sq->drawCenteredScaled(container->getWidth()*0.5f, container->getHeight() * 0.5f, 2.0f, 2.0f);
		r->fillCircle(accel_position.x, accel_position.y, 15, 30);
	}

	if (scenario == SCENARIO_JUMP) {

		r->setDrawColor(Color::white);

		float w = 40;
		float h = 40;

		// regular
		r->fillRect((container->getWidth()*0.23f) - (w*0.5f), jump_position.y - (h * 1.0f), w, h);

		// s & s
		float wss = w;
		float hss = h;
		if (jump_timer > 0.0f) {
			float stretch = Easing::easebetween(Easing::QUADRATIC_IN_OUT, jump_timer, jump_stretch, 1.0f, jump_duration);
			float squash = Easing::easebetween(Easing::QUADRATIC_IN_OUT, jump_timer, jump_squash, 1.0f, jump_duration);
			wss *= squash;
			hss *= stretch;
		}
		r->fillRect((container->getWidth()*0.5f) - (wss*0.5f), jump_position.y - (hss * 1.0f), wss, hss);

		// s & s & e
		wss = w;
		hss = h;
		if (jump_timer > 0.0f) {
			float stretch = Easing::easebetween(Easing::QUADRATIC_IN_OUT, jump_timer, jump_stretch*1.2f, 1.0f, jump_duration);
			float squash = Easing::easebetween(Easing::QUADRATIC_IN_OUT, jump_timer, jump_squash*0.8f, 1.0f, jump_duration);
			wss *= squash;
			hss *= stretch;
		}
		if (jump_landtimer > 0.0f) {
			float stretch = Easing::easebetween(Easing::QUADRATIC_IN_OUT, jump_landtimer, jump_stretch, 1.0f, jump_landduration);
			float squash = Easing::easebetween(Easing::QUADRATIC_IN_OUT, jump_landtimer, jump_squash, 1.0f, jump_landduration);
			wss *= stretch;
			hss *= squash;
		}
		r->fillRect((container->getWidth()*0.77f) - (wss*0.5f), jump_position.y - (hss * 1.0f), wss, hss);

		r->setLineWidth(2);
		r->drawLine(50.0f, jumpLineY, container->getWidth() - 50.0f, jumpLineY);
	}


	if (scenario == SCENARIO_CAMERATWEENS) {

		r->setLineWidth(2);
		r->setDrawColor(Color::white);

		float topY = (container->getHeight()*0.25f);
		float sndY = (container->getHeight()*0.55f);
		float cameraW = 150;
		float cameraH = cameraW * (9.0f/16.0f);

		float cameraICNSC = 0.5f;
		float cameraLeft = 50;
		float cameraRight = (container->getWidth()-50-cameraW);
		float cameraTopX = (camera_state == 0)?50:cameraRight;
		float cameraSndX = (camera_state == 0)?50:cameraRight;

		if (camera_timer > 0.0f) {
			if (camera_state == 0) {
				cameraTopX = Easing::easebetween(Easing::QUADRATIC_OUT,    camera_timer, cameraLeft, cameraRight, camera_duration);
				cameraSndX = Easing::easebetween(Easing::QUADRATIC_IN_OUT, camera_timer, cameraLeft, cameraRight, camera_duration);
			}
			else if (camera_state == 1) {
				cameraTopX = Easing::easebetween(Easing::QUADRATIC_OUT,    camera_timer, cameraRight, cameraLeft, camera_duration);
				cameraSndX = Easing::easebetween(Easing::QUADRATIC_IN_OUT, camera_timer, cameraRight, cameraLeft, camera_duration);
			}
		}

		r->drawRect( cameraTopX, topY - (cameraH * 0.5f), cameraW, cameraH);
		r->drawRect( cameraSndX, sndY - (cameraH * 0.5f), cameraW, cameraH);

		cam->drawCenteredScaled(cameraTopX + (cameraW*0.5f), topY, cameraICNSC, cameraICNSC);
		cam->drawCenteredScaled(cameraSndX + (cameraW*0.5f), sndY, cameraICNSC, cameraICNSC);

		r->setDrawColor(Color::white_50a);
		r->drawRect(50, topY - (cameraH * 0.5f), container->getWidth()-100, cameraH);
		r->drawRect(50, sndY - (cameraH * 0.5f), container->getWidth()-100, cameraH);

	}

	if (scenario == SCENARIO_EASINGS) {

		r->setLineWidth(2);
		r->setDrawColor(Color::white);

		float lx = 150;
		float rx = container->getWidth() - 150;

		float sx = (easings_state == 0)?lx:rx;
		float ex = (easings_state == 0)?rx:lx;

		float d1 = Easing::easebetween(Easing::LINEAR, 				easings_timer, sx, ex, easings_duration - 1.0);
		float d2 = Easing::easebetween(Easing::QUADRATIC_OUT, 		easings_timer, sx, ex, easings_duration - 1.0);
		//float d3 = Easing::easebetween(Easing::QUADRATIC_IN_OUT, 	easings_timer, sx, ex, easings_duration - 1.0);
		//float d4 = Easing::easebetween(Easing::QUADRATIC_IN, 		easings_timer, sx, ex, easings_duration - 1.0);
		float d5 = Easing::easebetween(Easing::ELASTIC_OUT, 		easings_timer, sx, ex, easings_duration - 1.0);
		float d6 = Easing::easebetween(Easing::BOUNCE_OUT, 			easings_timer, sx, ex, easings_duration - 1.0);
		float d7 = Easing::easebetween(Easing::BACK_OUT, 			easings_timer, sx, ex, easings_duration - 1.0);

		r->fillCircle(d1,  50, 10, 30);
		r->fillCircle(d2, 100, 10, 30);
		r->fillCircle(d5, 150, 10, 30);
		r->fillCircle(d6, 200, 10, 30);
		r->fillCircle(d7, 250, 10, 30);
		//r->fillCircle(d6, 300, 10, 30);
		//r->fillCircle(d7, 350, 10, 30);

	}

	if (scenario == SCENARIO_MOVEMENTS) {

		r->setLineWidth(2);
		r->setDrawColor(Color::white);


		//float enemybobtimer;
		//float enemybobduration;
		float hx = container->getWidth()*0.25f;
		float hx2 = container->getWidth()*0.75f;
		float hy = container->getHeight()*0.5f;
		float hsc = 5.0f;
		float hopY = 0;
		float bobheight = 5.0f;
		hopY = Easing::easebetweenback(Easing::QUADRATIC_OUT, Easing::QUADRATIC_IN, enemybobtimer, 0.0f, bobheight, enemybobduration);
		enemybob->drawAligned(hx, hy - hopY, Renderer::ALIGN_CENTER, Renderer::ALIGN_BOTTOM, hsc, hsc);

		float rotation = 0.0f;
		float qwd = m_walkWobbleDuration*0.25f;

	    if (m_walkWobbleTimer > 0.0f) {
	    	//ARK2D::getLog()->e(StringUtil::appendf("m_walkWobbleTimer", m_walkWobbleTimer));
			if (m_walkWobbleTimer <= qwd) {
				rotation = Easing::easebetween(Easing::LINEAR, m_walkWobbleTimer, 0.0f, -m_walkWobbleMaxRotation, qwd);
			} else if (m_walkWobbleTimer <= qwd*3) {
				rotation = Easing::easebetween(Easing::LINEAR, m_walkWobbleTimer-qwd, -m_walkWobbleMaxRotation, m_walkWobbleMaxRotation, qwd*2);
			} else if (m_walkWobbleTimer <= qwd*4) {
				rotation = Easing::easebetween(Easing::LINEAR, m_walkWobbleTimer-(qwd*3), m_walkWobbleMaxRotation, 0.0f, qwd);
			}
		}
		playerbob->setRotation(rotation);
		playerbob->drawPivoted(hx2, hy, 4.5f * hsc, 13.0f * hsc, 1.0f);



		float szb = 50.0f;
		r->drawLine(hx - szb, hy + 1, hx + szb, hy + 1);
		r->drawLine(hx2 - szb, hy + 1, hx2 + szb, hy + 1);
	}

	if (scenario == SCENARIO_CONTINUITY) {
		float sc = 1.5f;
		float hx = container->getWidth()*0.3f;
        float hxm = container->getWidth()*0.5f;
		float hx2 = container->getWidth()*0.7f;
		float hy = container->getHeight()*0.4f;

		if (bird_explode_timer == 0.0f) {
			bird->getCurrentFrame()->drawCenteredScaled(hx, hy, sc, sc);
		}
		if (bird_explode_timer > 0.0f) {
			explosion->getCurrentFrame()->drawCenteredScaled(hx, hy, sc, sc);
		}

		if (bird_explode_timer < 0.25f) {
			bird->getCurrentFrame()->drawCenteredScaled(hx2, hy, sc, sc);
		}
		if (bird_explode_timer > 0.0f) {
			explosion->getCurrentFrame()->drawCenteredScaled(hx2, hy, sc, sc);
		}
	}

	if (scenario == SCENARIO_PARTICLES1 || scenario == SCENARIO_PARTICLES2 || scenario == SCENARIO_PARTICLES3) {
		particletile->drawCenteredScaled(p1x1, container->getHeight() * 0.5f, 1.0f, 1.0f);
		particletile->drawCenteredScaled(p1x2, container->getHeight() * 0.5f, 1.0f, 1.0f);

		for(int i = 0; i < particle1s.size(); i++) {
			Particle1* p1 = particle1s[i];
			float sc = 2.0f;
			if (scenario == SCENARIO_PARTICLES3) {
				sc = Easing::easebetween(Easing::QUADRATIC_IN, p1->time, 2.0f, 0.0f, p1->duration);
			}
			particlefx1->reset();
			//particlefx1->setTime();
			float t = Easing::easebetween(Easing::QUADRATIC_OUT, p1->time, 0.0f, 1.0f, p1->duration);
			particlefx1->update(t * (particlefx1->getFrameTime() * particlefx1->size()));
			particlefx1->getCurrentFrame()->drawCenteredScaled(p1->x, p1->y, sc, sc);
		}
	}



}

InGameState::~InGameState() {

}

