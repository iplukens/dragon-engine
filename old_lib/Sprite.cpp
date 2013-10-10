/*
 * Sprite.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: ian
 */

#include "Sprite.h"
#include <curses.h>

#define COLOR_DEFAULT COLOR_WHITE

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

// Create sprite with indicated maximum number of frames.
Sprite::Sprite(int max_frames) {
	max_frame_count = max_frames;
	width = 0;
	height = 0;
	frame_count = 0;
	frame = new Frame [max_frames];
	color = COLOR_DEFAULT;
}
// Get width of sprite.
int Sprite::getWidth(){
	return width;
}
// Set width of sprite.
void Sprite::setWidth(int new_width){
	width = new_width;
}
// Get height of sprite.
int Sprite::getHeight(){
	return height;
}
// Set height of sprite.
void Sprite::setHeight(int new_height){
	height = new_height;
}
// Get sprite color.
int Sprite::getColor(){
	return color;
}
// Set sprite color.
void Sprite::setColor(int new_color){
	color = new_color;
}
// Get total count of frames in sprite.
int Sprite::getFrameCount(){
	return frame_count;
}
// Get next sprite frame indicated by number.
// Return empty frame if out of range [0, frame_count].
Frame Sprite::getFrame(int frame_number){
	if (frame_number < frame_count){
		return frame[frame_number];
	}
	else{
		return Frame();
	}
}
// Add frame to sprite.
// Return -1 if frame array full, else 0.
int Sprite::addFrame(Frame new_frame){
	int result = -1;
	if (frame_count < max_frame_count){
		frame[frame_count] = new_frame;
		frame_count++;
		result = 0;
	}
	return result;
}
// Get label associated with sprite.
string Sprite::getLabel(){
	return label;
}
// Set label associated with sprite.
void Sprite::setLabel(string new_label){
	label = new_label;
}
