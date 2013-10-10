/*
 * EndOfWorlds.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: ian
 */

#include "EndOfWorlds.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventCollision.h"

EndOfWorlds::EndOfWorlds(int in_life, int x, int y) {
	ResourceManager &rm = ResourceManager::getInstance();
	LogManager &lm = LogManager::getInstance();

	life = in_life;
	setXVelocity(in_life);
	step_count = 0;
	setType("EndOfWorlds");
	setSolidness(SOFT);
	Position p(x, y);
	Sprite *p_temp_sprite;
	lm.writeLog("Getting the sprite");
	p_temp_sprite = rm.getSprite("ship");
	lm.writeLog("making it");
	if (!p_temp_sprite) {
		lm.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "ship");
	} else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3);		// third speed animation
		lm.writeLog("Load looks like:\n%s", p_temp_sprite->getFrame(0).getString().c_str());
	}
	setPosition(p);
	lm.writeLog("EndOfWorlds set at position %d, %d", this->getPosition().getX(), this->getPosition().getY());
	registerInterest(STEP_EVENT);
	registerInterest(KEYBOARD_EVENT);
	registerInterest(OUT_EVENT);
	registerInterest(COLLISION_EVENT);
}

void EndOfWorlds::draw(){
}

int EndOfWorlds::eventHandler(Event *p_e){
	GameManager &gm = GameManager::getInstance();
	LogManager &lm = LogManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();
	if (p_e->getType() == "__step__"){
		lm.writeLog("End of Worlds got a step event, increasing its step counter: %d", ++step_count);
		lm.writeLog("At position %d, %d", getPosition().getX(), getPosition().getY());
		return 1;
	}
	if (p_e->getType() == KEYBOARD_EVENT){
		lm.writeLog("Got a keyboard event!");
		EventKeyboard *k_e = static_cast<EventKeyboard *>(p_e);
		lm.writeLog("keyboard call for end o' worlds %c", k_e->getKey());
		if(k_e->getKey() == 'x'){
			lm.writeLog("Ending game because you pressed x");
			gm.setGameOver();
		}
		return 1;
	}
	if (p_e->getType() == OUT_EVENT){
		lm.writeLog("I'm GONE!");
	}
	if (p_e->getType() == COLLISION_EVENT){
		lm.writeLog("OW, WE HAVE COLLIDED!");
	}
	return 0;
}

EndOfWorlds::~EndOfWorlds() {
	// TODO Auto-generated destructor stub
}
