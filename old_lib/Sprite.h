/*
 * Sprite.h
 *
 *  Created on: Oct 1, 2013
 *      Author: ian
 */

#ifndef __SPRITE_H_
#define __SPRITE_H_

#include <string>
#include "Frame.h"
using std::string;
class Sprite {
private:
	int width; // Sprite width.
	int height; // Sprite height.
	int max_frame_count; // Maximum number of frames sprite can have.
	int frame_count; // Actual number of frames sprite has.
	int color; // Optional color for entire sprite.
	Frame *frame; // Array of frames.
	string label; // Text label to identify sprite.
	Sprite(); // Sprite constructor always has one arg.
public:
// Destroy sprite, deleting any allocated frames.
	~Sprite();
// Create sprite with indicated maximum number of frames.
	Sprite(int max_frames);
// Get width of sprite.
	int getWidth();
// Set width of sprite.
	void setWidth(int new_width);
// Get height of sprite.
	int getHeight();
// Set height of sprite.
	void setHeight(int new_height);
// Get sprite color.
	int getColor();
// Set sprite color.
	void setColor(int new_color);
// Get total count of frames in sprite.
	int getFrameCount();
// Get next sprite frame indicated by number.
// Return empty frame if out of range [0, frame_count].
	Frame getFrame(int frame_number);
// Add frame to sprite.
// Return -1 if frame array full, else 0.
	int addFrame(Frame new_frame);
// Get label associated with sprite.
	string getLabel();
// Set label associated with sprite.
	void setLabel(string new_label);
};

#endif /* SPRITE_H_ */
