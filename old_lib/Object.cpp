/*
 * Object.cpp
 *
 *  Created on: Sep 14, 2013
 *      Author: ian
 */

#include "Object.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"

#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

#include "Math.h"

Object::Object() {
	solidness = SOFT;
	altitude = 0;
	event_count = 0;
	WorldManager &wm = WorldManager::getInstance();
	wm.insertObject(this);
	x_velocity = 0;
	y_velocity = 0;
	x_velocity_countdown = 0;
	y_velocity_countdown = 0;
	sprite_center = false;
	sprite_index = 0;
	sprite_slowdown = 0;
	sprite_slowdown_count = 0;
	p_sprite = NULL;
	box = Box();
}

Object::~Object() {
	LogManager &lm = LogManager::getInstance();
	for (int i = event_count - 1; i >= 0; i--) {
		lm.writeLog("Unregistering: %s", event_list[i].c_str());
		unregisterInterest(event_list[i]);
	}
	WorldManager &wm = WorldManager::getInstance();
	wm.removeObject(this);
}

// Set type identifier of object.
void Object::setType(string new_type) {
	type = new_type;
}
// Get type identifier of object.
string Object::getType() {
	return type;
}
// Set Position of object.
void Object::setPosition(Position new_pos) {
	pos = new_pos;
}
// Get Position of object.
Position Object::getPosition() {
	return pos;
}

int Object::eventHandler(Event *p_event) {
	return 0;
}

// registers interest in an event; returns 0 if registered; -1 if not
int Object::registerInterest(string event_name) {
	int result = -1;
	for (int i = 0; i < event_count - 1; i++) {
		// already registered!
		if (event_list[i] == event_name) {
			return 0;
		}
	}
	if (event_count >= MAX_OBJ_EVENTS) {
		// too many events!
		return -1;
	} else if (event_name == EVENT_STEP) {
		GameManager &gm = GameManager::getInstance();
		result = gm.registerInterest(this, event_name);
	} else if (event_name == MOUSE_EVENT || event_name == KEYBOARD_EVENT) {
		InputManager &im = InputManager::getInstance();
		result = im.registerInterest(this, event_name);
	} else {
		WorldManager &wm = WorldManager::getInstance();
		result = wm.registerInterest(this, event_name);
	}
	if (result != -1) {
		event_list[event_count] = event_name;
		event_count++;
	}
	return result;
}

// unregisters interest in events; return 0 if good; -1 if not
int Object::unregisterInterest(string event_name) {
	int result = -1;
	if (event_name == EVENT_STEP) {
		GameManager &gm = GameManager::getInstance();
		result = gm.unregisterInterest(this, event_name);
	} else if (event_name == MOUSE_EVENT || event_name == KEYBOARD_EVENT) {
		InputManager &im = InputManager::getInstance();
		result = im.unregisterInterest(this, event_name);
	} else {
		WorldManager &wm = WorldManager::getInstance();
		result = wm.unregisterInterest(this, event_name);
	}
	return result;
}

void Object::draw() {
	// Ask graphics manager to draw current frame.
	GraphicsManager &gm = GraphicsManager::getInstance();
	gm.drawFrame(pos, p_sprite->getFrame(sprite_index), p_sprite->getColor(),
			sprite_center);
	// If slowdown is 0, then animation is frozen.
	if (getSpriteSlowdown() == 0) {
		return;
	}
	// Increment counter.
	int count = getSpriteSlowdownCount();
	count++;
	// Advance sprite index, if appropriate.
	if (count >= getSpriteSlowdown()) {
		count = 0; // Reset counter.
		sprite_index++;
		// If at last frame, loop to beginning.
		if (sprite_index >= p_sprite->getFrameCount()) {
			sprite_index = 0;
		}
		setSpriteSlowdownCount(count); // Set counter for next draw().
	}
}

int Object::setAltitude(int new_altitude) {
	int result = -1;
	if (altitude <= MAX_ALTITUDE && altitude >= 0) {
		altitude = new_altitude;
		result = 0;
	}
	return result;
}

int Object::getAltitude() {
	return altitude;
}

// Get and set velocity (x,y).
void Object::setXVelocity(float new_x_velocity) {
	x_velocity = new_x_velocity;
	x_velocity_countdown = 1;
}
float Object::getXVelocity() {
	return x_velocity;
}
void Object::setYVelocity(float new_y_velocity) {
	y_velocity = new_y_velocity;
	y_velocity_countdown = 1;
}
float Object::getYVelocity() {
	return y_velocity;
}
// Perform 1 step of velocity in horizontal direction.
// Return horizontal distance moved this step.
int Object::getXVelocityStep() {
	// See if object has velocity.
	if (x_velocity == 0) {
		return 0;
	}
	// See if moving this step.
	x_velocity_countdown -= fabs(x_velocity);
	if (x_velocity_countdown > 0) {
		return 0;
	}
	// Moving this step, so figure out how far.
	int spaces = floor(1 - x_velocity_countdown);
	x_velocity_countdown = 1 + fmod(x_velocity_countdown, 1);
	// Return number of spaces to move.
	if (x_velocity > 0) {
		return spaces;
	} else
		return -1 * spaces;
}

// Perform 1 step of velocity in vertical direction.
// Return vertical distance moved this step.
int Object::getYVelocityStep() {
	// See if object has velocity.
	if (y_velocity == 0) {
		return 0;
	}
	// See if moving this step.
	y_velocity_countdown -= fabs(y_velocity);
	if (y_velocity_countdown > 0) {
		return 0;
	}
	// Moving this step, so figure out how far.
	int spaces = floor(1 - y_velocity_countdown);
	y_velocity_countdown = 1 + fmod(y_velocity_countdown, 1);
	// Return number of spaces to move.
	if (y_velocity > 0) {
		return spaces;
	} else
		return -1 * spaces;
}

// True if HARD or SOFT, else False.
bool Object::isSolid() {
	return solidness == HARD || solidness == SOFT;
}
// Set object solidness, with checks for consistency.
// Return 0 if ok, else -1.
int Object::setSolidness(Solidness new_solid) {
	int result = -1;
	if (solidness == HARD || solidness == SOFT || solidness == SPECTRAL)
		solidness = new_solid;
	return result;
}
// Return object solidness.
Solidness Object::getSolidness() {
	return solidness;
}

// Set Sprite associated with this object to new one.
// Set bounding box to size of sprite.
void Object::setSprite(Sprite *p_new_sprite) {
	p_sprite = p_new_sprite;
}
// Set object Sprite to new one.
// If set_box is true, set bounding box to size of Sprite.
void Object::setSprite(Sprite *p_new_sprite, bool set_box) {
	p_sprite = p_new_sprite;
	box = Box(pos, p_new_sprite->getWidth(), p_new_sprite->getHeight());
}
// Return pointer to Sprite associated with this object.
Sprite * Object::getSprite() {
	return p_sprite;
}
// Set Sprite to be centered at object Position (pos).
void Object::setCentered(bool centered) {
	sprite_center = centered;
}

// Indicates if sprite is centered at object Position (pos).
bool Object::isCentered() {
	return sprite_center;
}
// Set index of current Sprite frame to be displayed.
void Object::setSpriteIndex(int new_sprite_index) {
	sprite_index = new_sprite_index;
}
// Return index of current Sprite frame to be displayed.
int Object::getSpriteIndex() {
	return sprite_index;
}
// Slows down sprite animations.
// Sprite slowdown is in multiples of GameManager frame time.
void Object::setSpriteSlowdown(int new_sprite_slowdown) {
	sprite_slowdown = new_sprite_slowdown;
}
int Object::getSpriteSlowdown() {
	return sprite_slowdown;
}
void Object::setSpriteSlowdownCount(int new_sprite_slowdown_count) {
	sprite_slowdown_count = new_sprite_slowdown_count;
}
int Object::getSpriteSlowdownCount() {
	return sprite_slowdown_count;
}

void Object::setBox(Box new_box){
	box = new_box;
}

Box Object::getBox(){
	return box;
}
