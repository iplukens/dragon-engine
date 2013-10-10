/*
 * Clock.h
 *
 *  Created on: Sep 12, 2013
 *      Author: ian
 */

#ifndef __CLOCK_H_
#define __CLOCK_H_

#ifdef MACOS
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
#endif

#ifdef CYGWIN
#include <time.h>

class Clock {

 private:
  struct timespec prev_ts;  // Store previous time called.

 public:
  // Sets prev_ts to current time.
  Clock();

  // Return time elapsed since delta() was called.
  // Units are microseconds.
  long int delta(void);

  // Return time elapsed since delta() was last called.
  // Units are microseconds.
  long int split(void);

};
#endif

#endif /* CLOCK_H_ */
