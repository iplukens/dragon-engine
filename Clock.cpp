/*
 * Clock.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: ian
 */

#ifdef MACOS
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
#elif CYGWIN
#include <time.h>

#include "Clock.h"

Clock::Clock(){
	clock_gettime(CLOCK_REALTIME, &prev_ts);
}

long int Clock::delta(){
	struct timespec current_ts;
	clock_gettime(CLOCK_REALTIME, &current_ts);

	long int before_msec, after_msec;
	before_msec = prev_ts.tv_sec*1000 + prev_ts.tv_nsec/10000000;
	after_msec = current_ts.tv_sec*1000 + current_ts.tv_nsec/1000000;
	long int elapsed_time = after_msec - before_msec;

	prev_ts = current_ts;

	return elapsed_time;
}

long int Clock::split(){
	struct timespec current_ts;
	clock_gettime(CLOCK_REALTIME, &current_ts);

	long int before_msec, after_msec;
	before_msec = prev_ts.tv_sec*1000 + prev_ts.tv_nsec/10000000;
	after_msec = current_ts.tv_sec*1000 + current_ts.tv_nsec/1000000;
	long int elapsed_time = after_msec - before_msec;

	return elapsed_time;
}
#endif
