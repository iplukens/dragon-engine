/*
 * Clock.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: ian
 */
#ifndef NULL
#define NULL   ((void *) 0)
#endif
#include "Clock.h"
#include "LogManager.h"

// sets the current time to prev_ts
Clock::Clock() {
	timeval time;
	gettimeofday(&time, NULL);
	prev_ts = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

// returns the time since delta was last called and sets prev_ts to the current time
// time is reported in milliseconds
long int Clock::delta(){
	timeval time;
	long int old_millis = prev_ts;
	gettimeofday(&time, NULL);
	prev_ts = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	LogManager &lm = LogManager::getInstance();
	return prev_ts - old_millis;
}

// returns the time since delta was last called
// time is reported in milliseconds
long int Clock::split(){
	LogManager &lm = LogManager::getInstance();
	timeval new_ts;
	gettimeofday(&new_ts, NULL);
	long int new_millis = (new_ts.tv_sec * 1000) + (new_ts.tv_usec / 1000);
	long int result = new_millis - prev_ts;
	return result;
}
