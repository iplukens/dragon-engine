/*
 * LogManager.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: ian
 */
#ifndef NULL
#define NULL   ((void *) 0)
#endif
#include "LogManager.h"

LogManager::LogManager() {
	do_flush = false;
	fp = fopen(LOGFILE_NAME, "w");
}

LogManager &LogManager::getInstance() {
	static LogManager instance; // Guaranteed to be destroyed.
								// Instantiated on first use.
	return instance;
}

int LogManager::startUp(bool flush){
	do_flush = flush;
	fp = fopen(LOGFILE_NAME, "w");
	if(fp == NULL){
		return -1;
	}
	return Manager::startUp();
}

int LogManager::writeLog(const char *fmt, ...) {
	fprintf(fp, "\nMessage: ");
	va_list args;
	va_start(args, fmt);
	vfprintf(fp, fmt, args);
	va_end(args);
	if (do_flush) {
		fflush(fp);
	}
	return 0;
}

int LogManager::shutDown(){
	writeLog("LogManager shutting down");
	fclose(fp);
	return Manager::shutDown();
}

LogManager::~LogManager() {
}

bool LogManager::isValid(string event_name){
	return false;
}
