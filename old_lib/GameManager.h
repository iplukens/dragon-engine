/*
 * GameManager.h
 *
 *  Created on: Sep 12, 2013
 *      Author: ian
 */

#ifndef __GAMEMANAGER_H_
#define __GAMEMANAGER_H_

#include "Manager.h"
#include "ObjectList.h"

class GameManager : public Manager {
public:
	static GameManager &getInstance();
	int startUp();
	int shutDown();

	// Run game loop.
	// fr_time is time between frames in milliseconds.
	void run(int fr_time=30);

	// Set game over status to indicated value.
	// If true (the default), will stop game loop.
	void setGameOver(bool new_game_over=true);

	// Return frame time.
	// Frame time is target time for game loop, in milliseconds.
	int getFrameTime();

private:
	GameManager();
	GameManager (GameManager const&); // No copying.
	void operator=(GameManager const&); // No assignment.
	bool game_over; // True, then game loop should stop.
	int frame_time; // Target time per game loop (in milliseconds).
	// check if an event is valid
	virtual bool isValid(string event_name);
};

#endif /* GAMEMANAGER_H_ */
