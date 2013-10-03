/*
 * Frame.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: ian
 */

#include "Frame.h"

Frame::Frame() {
	// TODO Auto-generated constructor stub
	width = 0;
	height = 0;
	frame_str = "";
}

// Create frame of indicated width and height with string.
Frame::Frame(int new_width, int new_height, string new_str) {
	width = new_width;
	height = new_height;
	frame_str = new_str;
}
// Get width of frame.
int Frame::getWidth() {
	return width;
}
// Set width of frame.
void Frame::setWidth(int new_width) {
	width = new_width;
}
// Get height of frame.
int Frame::getHeight() {
	return height;
}
// Set height of frame.
void Frame::setHeight(int new_height) {
	height = new_height;
}
// Get frame characters (stored as string).
string Frame::getString() {
	return frame_str;
}
// Set frame characters (stored as string).
void Frame::setFrame(string new_frame_str) {
	frame_str = new_frame_str;
}
