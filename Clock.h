/*
 * Clock.h
 *
 *  Created on: Sep 12, 2013
 *      Author: ian
 */

#ifndef __CLOCK_H_
#define __CLOCK_H_

#include <sys/time.h>

class Clock {
private:
int prev_ts; // Stores previous time delta() called in milliseconds
public:
// Sets prev_ts to current time.
Clock();
// Stamps a current time
long int delta(void);
// Return time elapsed since delta() was last called.
// Units are microseconds.
long int split(void);
};

#endif /* CLOCK_H_ */
