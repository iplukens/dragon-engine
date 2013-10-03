/*
 * LogManager.h
 *
 *  Created on: Sep 12, 2013
 *      Author: ian
 */

#ifndef __LOGMANAGER_H_
#define __LOGMANAGER_H_

#include "Manager.h"
#include <stdio.h>
#include <stdarg.h>

#define LOGFILE_NAME "dragonfly.log"

class LogManager : public Manager {
private:
	LogManager();
	bool do_flush; // whether or not logs flush
	FILE *fp; // pointer to log file
	LogManager (LogManager const&);    ///< Don't allow copy.
	void operator=(LogManager const&); ///< Don't allow assignment.
	bool isValid(string event_name);
public:
	static LogManager &getInstance();
	~LogManager();
	/// Start up LogManager (open logfile "dragonfly.log").
	/// If flush is true, then call fflush() afer each write.
	int startUp(bool flush = false);

	/// Shut down LogManager (close logfile).
	int shutDown();

	/// Write to logfile.
	/// Supports printf() formatting of strings.
	/// Return bytes written (excluding time), -1 if error
	int writeLog(const char *fmt, ...);
};

#endif /* LOGMANAGER_H_ */
