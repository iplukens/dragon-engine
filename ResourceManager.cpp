/*
 * ResourceManager.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: ian
 */

#include "ResourceManager.h"
#include "LogManager.h"
#include <iostream>
#include <fstream>
using std::ifstream;
using std::cout;
using std::endl;

// util functions
int readLineInt(ifstream *p_file, int *p_line_number, const char *tag);
Frame readFrame(ifstream *p_file, int *p_line_number, int width, int height);


ResourceManager::ResourceManager() {
	sprite_count = 0;
}

ResourceManager::~ResourceManager() {
}

// Get the one and only instance of the ResourceManager.
ResourceManager &ResourceManager::getInstance() {
	static ResourceManager instance; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return instance;
}
// Get manager ready for resources.
int ResourceManager::startUp() {
	return Manager::startUp();
}
// Shut down manager, freeing up any allocated Sprites.
int ResourceManager::shutDown() {
	return Manager::shutDown();
}
// Load Sprite from file.
// Assign indicated label to sprite.
// Return 0 if ok, else -1.
int ResourceManager::loadSprite(string filename, string label) {
	LogManager &lm = LogManager::getInstance();
	int result = -1;
	ifstream p_file (filename.c_str());
	int line_number = 0;
	if (p_file.is_open()) {
		int frame_count = readLineInt(&p_file, &line_number, FRAMES_TOKEN);
		int width = readLineInt(&p_file, &line_number, WIDTH_TOKEN);
		int height = readLineInt(&p_file, &line_number, HEIGHT_TOKEN);
		if (width == -1 || height == -1 || frame_count == -1)
			return -1;
		Sprite* new_guy = new Sprite(frame_count);
		for (int i = 0; i < frame_count; i++) {
			try{
				Frame new_frame = readFrame(&p_file, &line_number, width, height);
				new_guy->addFrame(new_frame);
			} catch (char* e){
				p_file.close();
				return -1;
			}
		}
		p_file.close();
		new_guy->setLabel(label);
		p_sprite[sprite_count] = new_guy;
		sprite_count++;
	}
	return result;
}
// Unload Sprite with indicated label.
// Return 0 if ok, else -1.
int ResourceManager::unloadSprite(string label) {
	int result = -1;
	for (int i = 0; i < sprite_count - 1; i++) {
		if (p_sprite[i]->getLabel() == label) {
			delete p_sprite[i];
			sprite_count--;
			for (int j = i; j < sprite_count - 1; j++) {
				p_sprite[i] = p_sprite[i + 1];
			}
			result = 0;
		}
	}
	return result;
}
// Find Sprite with indicated label.
// Return pointer to it if found, else NULL.
Sprite *ResourceManager::getSprite(string label) {
	LogManager &lm = LogManager::getInstance();
	Sprite* result = NULL;
	for (int i = 0; i < sprite_count; i++) {
		lm.writeLog("checking sprite %d of %d", i, sprite_count);
		if (p_sprite[i]->getLabel() == label) {
			result = p_sprite[i];
			lm.writeLog("got it!");
			break;
		}
	}
	return result;
}

// Read single line of form `tag number', return number.
int readLineInt(ifstream *p_file, int *p_line_number, const char *tag) {
	LogManager &lm = LogManager::getInstance();
	string name;
	std::getline(*p_file, name);
	unsigned pch = name.find(" ");
	if (!pch) {
		lm.writeLog("Could not find the associated label");
		return -1;
	}
	const char* convert = name.substr(pch).c_str();

	int number = atoi(convert);

	lm.writeLog("%s: %d", tag, number);

	(*p_line_number)++;
	return number;
}

// Read frame until `eof', return Frame.
Frame readFrame(ifstream *p_file, int *p_line_number, int width, int height) {
	LogManager &lm = LogManager::getInstance();
	string line, frame_str;
	for (int i = 0; i < height; i++) {
		getline(*p_file, line, '\n');
		if (line.length() > width + 1) {
			lm.writeLog("Sprite width was greater than expected!");
			throw "width problem";
		}
		frame_str += line;
	}
	getline(*p_file, line);
	if (line.find("end")) {
		lm.writeLog(
				"Sprite frame height was higher than expected!");
		throw "height problem";
	}
	Frame frame(width, height, frame_str);
	return frame;
}
