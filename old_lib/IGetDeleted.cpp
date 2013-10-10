/*
 * IGetDeleted.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: ian
 */

#include "IGetDeleted.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "Position.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventOut.h"

IGetDeleted::IGetDeleted(int in_life) {
	life = in_life;
	step_counter = 0;
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("Making an IGetDeleted object of life %d", life);
	setType("IGetDeleted");
	Position p(5,5);
	setPosition(p);
	setSolidness(SPECTRAL);
	setXVelocity(-1);
	setAltitude(0);		// make them in the background
	registerInterest(EVENT_STEP);
	registerInterest(OUT_EVENT);
}

void IGetDeleted::draw() {
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	graphics_manager.drawCh(getPosition(), 'h');
}

int IGetDeleted::eventHandler(Event *p_e){
	LogManager &lm = LogManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();
	if (p_e->getType() == "__step__"){
		lm.writeLog("IGetDeleted of life %d got a step event, increasing its step counter: %d", life, ++step_counter);
		lm.writeLog("currently at position %d, %d", getPosition().getX(), getPosition().getY());
		if (step_counter == life){
			lm.writeLog("Marked for deletion as the step_counter is equal to its life of %d", life);
			wm.markForDelete(this);
		}
		return 1;
	}
	if (p_e->getType() == OUT_EVENT){
		lm.writeLog("I'm gone! SO move me back");
		setPosition(Position(6, 1));
	}
	return 0;
}

IGetDeleted::~IGetDeleted() {
	LogManager &lm = LogManager::getInstance();
	GameManager &gm = GameManager::getInstance();
	lm.writeLog("Life of %d is dead", life);
}

