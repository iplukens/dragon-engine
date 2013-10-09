/*
 * GraphicsManager.h
 *
 *  Created on: Sep 25, 2013
 *      Author: ian
 */

#ifndef __GRAPHICSMANAGER_H_
#define __GRAPHICSMANAGER_H_

#include <curses.h>
#include "Manager.h"
#include "Position.h"

#define COLOR_DEFAULT COLOR_WHITE

enum Justification {
	LEFT_JUSTIFIED, CENTER_JUSTIFIED, RIGHT_JUSTIFIED,
};

class GraphicsManager: public Manager {
private:
	GraphicsManager();
	GraphicsManager(GraphicsManager const&);
	void operator=(GraphicsManager const&);
	WINDOW *buffer; // Drawing buffer.

public:
	// Get the one and only instance of the GraphicsManager.
	static GraphicsManager &getInstance();
	// Get terminal ready for text-based display.
	// Return 0 if ok, else return negative number.
	int startUp();
	// Revert back to normal terminal display.
	int shutDown();
	// Draw a character at screen location (x,y) with color.
	// Return 0 if ok, else -1.
	int drawCh(Position world_pos, char ch, int color = COLOR_DEFAULT);
	// Return display's horizontal maximum.
	int getHorizontal();
	// Return display's vertical maximum.
	int getVertical();
	// Render current display buffer.
	// Return 0 if ok, else -1.
	int swapBuffers();
	// Return Curses drawing window.
	WINDOW *getBuffer();
	// Draw string at screen location (x,y) with default color.
	// Justified LEFT, CENTER or RIGHT.
	// Note: top-left coordinate is (0,0).
	// Return 0 if ok, else -1.
	int drawString(Position world_pos, string str, Justification just,
			int color = COLOR_DEFAULT);
	// draws a frame of a sprite
	int drawFrame(Position world_pos, Frame frame, bool centered, int color);

//	bool isValid(string event_name);
};

#endif
