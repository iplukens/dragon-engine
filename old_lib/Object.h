/*
 * Object.h
 *
 *  Created on: Sep 14, 2013
 *      Author: ian
 */

#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <string>
#include "Position.h"
#include "Event.h"
#include "Sprite.h"
#include "Box.h"
using std::string;

#define MAX_OBJ_EVENTS 100

enum Solidness {
HARD, // Objects cause collisions and impede.
SOFT, // Objects cause collisions, but don't impede.
SPECTRAL // Objects don't cause collisions.
};

class Object {
private:
	Box box; // Box for sprite boundary & collisions
	enum Solidness solidness;
	int altitude;
	int event_count; // number of events the object is registered for
	string event_list[MAX_OBJ_EVENTS]; // array of all these events
	string type; // User-defined identification.
	Position pos; // Position in game world.
	float x_velocity; // Horizontal speed in spaces per step.
	float x_velocity_countdown; // Countdown to horizontal movement.
	float y_velocity; // Vertical speed in spaces per step.
	float y_velocity_countdown; // Countdown to vertical movement.
	Sprite *p_sprite; // Sprite associated with object.
	bool sprite_center; // True if sprite centered on object.
	int sprite_index; // Current index frame for sprite.
	int sprite_slowdown; // Slowdown rate (1 = no slowdown, 0 = stop).
	int sprite_slowdown_count; // Slowdown counter.
public:
	Object();
	virtual ~Object();
	// Set type identifier of object.
	void setType(string new_type);
	// Get type identifier of object.
	string getType();
	// Set Position of object.
	void setPosition(Position new_pos);
	// Get Position of object.
	Position getPosition();
	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1.
	virtual int eventHandler(Event *p_event);
	// return 0 if good; -1 if BAD
	int registerInterest(string event_name);
	int unregisterInterest(string event_name);
	virtual void draw();
	// return 0 if good; -1 if BAD
	int setAltitude(int new_altitude);
	// returns the altitude
	int getAltitude();
	// Get and set velocity (x,y).
	void setXVelocity(float new_x_velocity);
	float getXVelocity();
	void setYVelocity(float new_y_velocity);
	float getYVelocity();
	// Perform 1 step of velocity in horizontal direction.
	// Return horizontal distance moved this step.
	int getXVelocityStep();
	// Perform 1 step of velocity in vertical direction.
	// Return vertical distance moved this step.
	int getYVelocityStep();
	// returns true if solid; esle false
	bool isSolid();
	int setSolidness(enum Solidness new_solid);
	enum Solidness getSolidness();
	// Set Sprite associated with this object to new one.
	// Set bounding box to size of sprite.
	void setSprite(Sprite *p_new_sprite);
	// Set object Sprite to new one.
	// If set_box is true, set bounding box to size of Sprite.
	void setSprite(Sprite *p_new_sprite, bool set_box);
	// Return pointer to Sprite associated with this object.
	Sprite *getSprite();
	// Set Sprite to be centered at object Position (pos).
	void setCentered(bool centered);
	// Indicates if sprite is centered at object Position (pos).
	bool isCentered();
	// Set index of current Sprite frame to be displayed.
	void setSpriteIndex(int new_sprite_index);
	// Return index of current Sprite frame to be displayed.
	int getSpriteIndex();
	// Slows down sprite animations.
	// Sprite slowdown is in multiples of GameManager frame time.
	void setSpriteSlowdown(int new_sprite_slowdown);
	int getSpriteSlowdown();
	void setSpriteSlowdownCount(int new_sprite_slowdown_count);
	int getSpriteSlowdownCount();
	// set object's bounding box
	void setBox(Box new_box);
	// get object's bounging box
	Box getBox();
};

#endif
