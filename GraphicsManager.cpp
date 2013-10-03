/*
 * GraphicsManager.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: ian
 */

#include "GraphicsManager.h"
#include "LogManager.h"

GraphicsManager::GraphicsManager() {
	buffer = NULL;
}

int GraphicsManager::startUp() {
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("Graphics Manager is starting up.");
	if (initscr() != NULL) {
		buffer = newwin(0, 0, 0, 0);
		werase(buffer);
		clear();
		leaveok(buffer, true);
		if (has_colors() == true) {
			start_color();
			use_default_colors();
			assume_default_colors(COLOR_WHITE, COLOR_BLACK);
		}
		wattron(buffer, A_BOLD);
		return Manager::startUp();
	} else {
		return 1;
	}
}

int GraphicsManager::shutDown() {
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("GraphicsManager is shutting down.");
	endwin();
	return 0;
}

// horizontal maximum
int GraphicsManager::getHorizontal() {
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);
	return max_x;
}

// Return display's vertical maximum.
int GraphicsManager::getVertical() {
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);
	return max_y;
}

// Render current display buffer.
// Return 0 if ok, else -1.
int GraphicsManager::swapBuffers() {
	refresh();
	werase(buffer);
}
// Return Curses drawing window.
WINDOW* GraphicsManager::getBuffer() {
	return buffer;
}

GraphicsManager &GraphicsManager::getInstance() {
	static GraphicsManager instance; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return instance;
}

int GraphicsManager::drawCh(Position world_pos, char ch, int color) {
	int result = -1;
	if (wattron(buffer, COLOR_PAIR(color))) {
		if (mvwaddch(buffer, world_pos.getY(), world_pos.getX(), ch)) {
			if (wattroff(buffer, COLOR_PAIR(color))) {
				result = 0;
			}
		}
	}
	return result;
}

// Draw string at screen location (x,y) with default color.
// Justified left, center, or right.
// Note: top-left coordinate is (0,0).
// Return 0 if ok, else -1.
int GraphicsManager::drawString(Position world_pos, string str,
		Justification just, int color) {
// Get starting position.
	Position starting_pos = world_pos;
	switch (just) {
	case CENTER_JUSTIFIED:
		starting_pos.setX((world_pos.getX() - str.size()) / 2);
		break;
	case RIGHT_JUSTIFIED:
		starting_pos.setX(world_pos.getX() - str.size());
		break;
	case LEFT_JUSTIFIED:
		break;
	default:
		break;
	}
// Draw character by character.
	for (int i = 0; i < str.size(); i++) {
		Position temp_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(temp_pos, str[i], color);
	}
	return 0;
}

bool GraphicsManager::isValid(string event_name) {
	return false;
}

// Draw single sprite frame at screen location (x,y) with color.
// If centered true then center frame at (x,y).
// Return 0 if ok, else -1.
int GraphicsManager::drawFrame(Position world_pos, Frame frame, bool centered,
		int color) {
// Error check empty string.
	if (frame.getString() == "") {
		return -1;
	}
// Centered? Then offset (x,y) by 1/2 (width,height).
	int x_offset = 0;
	int y_offset = 0;
	if (centered) {
		x_offset = frame.getWidth() / 2;
		y_offset = frame.getHeight() / 2;
	}
// Frame data stored in string.
	string str = frame.getString();
// Draw character by character.
	for(int y = 1; y < frame.getHeight(); y++){
		for (int x = 1; x < frame.getWidth(); x++){
			Position temp_pos(world_pos.getX() - x_offset + x, world_pos.getY() - y_offset + y);
			drawCh(temp_pos, str[y * frame.getWidth() + x], color);
		}
	}
	return 0;
}
