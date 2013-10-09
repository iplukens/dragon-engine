#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "LogManager.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"

using std::string;
using std::ifstream;

//Helper functions
//Remove '\r' frome line (if there - typical of Windows)
void discardCR(string &str){
	if (str[str.size()-1] == '\r'){
		str.erase(str.size()-1);
	}
}

//Read single line of form 'tag number', return number
int readLineInt(ifstream *p_file, int *p_line_number, const char *tag){
	LogManager &log_manager = LogManager::getInstance();
	string line;

	getline(*p_file, line);
	discardCR(line);

	if (!line.compare(tag)){
		log_manager.writeLog("ResourceManager::loadSprite(): Error reading sprite! Expected tag of <%s> but was <%s> at line number <%d>", tag, line.c_str(), *p_line_number);
		return -1;
	}

	int start = (strlen(tag)+1);
	int end = line.length();

	int number = atoi(line.substr(start, end).c_str());

	(*p_line_number)++;

	log_manager.writeLog("ResourceManager::loadSprite() successfully read tag <%s> with a value of <%d>", tag, number);

	return number;
}

//Read single line of form 'tag number', return string
string readLine(ifstream *p_file, int *p_line_number, const char *tag){
	LogManager &log_manager = LogManager::getInstance();
	string line;

	getline(*p_file, line);
	discardCR(line);

	if (!line.compare(tag)){
		log_manager.writeLog("ResourceManager::loadSprite(): Error reading sprite! Expected tag of <%s> but was <%s> at line number <%d>", tag, line.c_str(), *p_line_number);
		return "";
	}

	int start = (strlen(tag) + 1);
	int end = line.length();

	string lineContent = line.substr(start, end).c_str();

	(*p_line_number)++;

	log_manager.writeLog("ResourceManager::loadSprite() successfully read tag <%s> with a value of <%s>", tag, lineContent.c_str());

	return lineContent;
}

//Read frame until 'end', return Frame
Frame readFrame(ifstream *p_file, int *p_line_number, int width, int height){
	LogManager &log_manager = LogManager::getInstance();
	string line;
	string frame_str = "";

	for (int i = 1; i <= height; i++){
		getline(*p_file, line);
		discardCR(line);
		*(p_line_number) += 1;

		//Error check
		if (line.length() > width){
			log_manager.writeLog("ResourceManager::loadSprite() Error reading frame! Expected width of <%d> but was <%d> at line number <%d>", width, line.length(), *p_line_number);
			Frame frame;
			return frame;
		}

		log_manager.writeLog("ResourceManager::loadSprite() Frame line loaded : <%s>", line.c_str());

		frame_str += line;
	}

	getline(*p_file, line);
	discardCR(line);
	*(p_line_number) += 1;

	if (line != END_FRAME_TOKEN){
		log_manager.writeLog("ResourceManager::loadSprite() Error reading frame! Expected <%s> at line number <%d> but was <%s>!", END_FRAME_TOKEN, *p_line_number, line.c_str());
		Frame frame;
		return frame;
	}

	//If end token found, increment line number
	*(p_line_number) += 1;

	Frame frame(width, height, frame_str);
	return frame;
}

//Convert color from a string to an int
int convertColor(string color_str){
	LogManager &log_manager = LogManager::getInstance();

	if (color_str == "black"){
		return COLOR_BLACK;
	} else if (color_str == "red"){
		return COLOR_RED;
	} else if (color_str == "green"){
		return COLOR_GREEN;
	} else if (color_str == "yellow"){
		return COLOR_YELLOW;
	} else if (color_str == "blue"){
		return COLOR_BLUE;
	}  else if (color_str == "magenta") {
		return COLOR_MAGENTA;
	} else if (color_str == "cyan") {
		return COLOR_CYAN;
	} else if (color_str == "white"){
		return COLOR_WHITE;
	} else if (color_str == "default"){
		return COLOR_DEFAULT;
	}

	log_manager.writeLog("ResourceManager::loadSprite() Error! Undefined color of <%s> used!", color_str.c_str());
	return -1;
}

//Actual class definition
ResourceManager::ResourceManager(){
	sprite_count = 0;
}

ResourceManager::~ResourceManager(){
		shutDown();
}


ResourceManager &ResourceManager::getInstance(){
	static ResourceManager resource_manager;
	return resource_manager;
}

int ResourceManager::startUp(){
	if (!is_started){
		is_started = true;
		sprite_count = 0;
	}

	LogManager& log_manager = LogManager::getInstance();
	log_manager.writeLog("ResourceManager::startUp() completed successfully");

	return 0;
}

int ResourceManager::shutDown(){
	is_started = false;

	//Delete all sprites
	for (int i = 0; i < sprite_count; i++){
			delete sprite[i];
	}

	sprite_count = 0;

	LogManager& log_manager = LogManager::getInstance();
	log_manager.writeLog("ResourceManager::shutDown() called");

	return 0;
}

int ResourceManager::loadSprite(string filename, string label){
	LogManager &log_manager = LogManager::getInstance();
	string line;
	ifstream spriteFile(filename.c_str());
	int lineNumber = 1;

	log_manager.writeLog("ResourceManager::loadSprite() attempting to load sprite <%s> from file <%s>", label.c_str() , filename.c_str());

	if (spriteFile.is_open()){

		//Read header
		int frames, width, height;
		string color;
		frames = readLineInt(&spriteFile, &lineNumber, FRAMES_TOKEN);
		width = readLineInt(&spriteFile, &lineNumber, WIDTH_TOKEN);
		height = readLineInt(&spriteFile, &lineNumber, HEIGHT_TOKEN);
		color = readLine(&spriteFile, &lineNumber, COLOR_TOKEN);

		//Error check
		if (frames == -1 || width == -1 || height == -1 || color == "") {
			log_manager.writeLog("ResourceManager::loadSprite() Encountered error when loading sprite from file <%s>!", filename.c_str());
			return -1;
		}

		//Add label and color to sprite
		Sprite* newSprite = new Sprite(frames);
		newSprite->setColor(convertColor(color));
		log_manager.writeLog("ResourceManager::loadSprite() Convert color of <%s> to <%d>", color.c_str(), newSprite->getColor());
		newSprite->setLabel(label);

		//Read body
		for (int i = 0; i < frames; i++){
			log_manager.writeLog("ResourceManager::loadSprite() attempting read frame at line number <%d>...", lineNumber);
			Frame frame = readFrame(&spriteFile, &lineNumber, width, height);
			newSprite->addFrame(frame);
		}

		//Check if at eof
		string eof_str;
		getline(spriteFile, eof_str);
		discardCR(eof_str);
		lineNumber++;

		if (eof_str != END_SPRITE_TOKEN){
			log_manager.writeLog("ResourceManager::loadSprite() expected <%s> at line number <%d> in file <%s>, was actually <%s>", END_SPRITE_TOKEN, lineNumber, filename.c_str(), eof_str.c_str());
			return -1;
		}

		//Add sprite
		sprite[sprite_count] = newSprite;
		sprite_count++;

		log_manager.writeLog("ResourceManager::loadSprite() set sprite_count to <%d>", sprite_count);
	}
	return 0;
}

int ResourceManager::unloadSprite(string label){
	LogManager &log_manager = LogManager::getInstance();
	log_manager.writeLog("ResourceManager::unloadSprite() called");

	for (int i = 0; i < sprite_count; i++){
		if (sprite[i]->getLabel() == label){

			delete sprite[i];

			//Shift array over
			for (int j = i; j < sprite_count; j++){
				sprite[j] = sprite[j+1];
			}
			sprite_count--;

			return 0;
		}
	}

	//Not found
	return -1;
}

Sprite* ResourceManager::getSprite(string label){
	LogManager &log_manager = LogManager::getInstance();
	log_manager.writeLog("ResourceManager::getSprite() called");

	for (int i = 0; i < sprite_count; i++){
		if (sprite[i]->getLabel() == label){
			log_manager.writeLog("ResourceManager::getSprite() found the correct sprite with label <%s>", label.c_str());
			return sprite[i];
		}
	}

	log_manager.writeLog("ResourceManager::getSprite() Error! Unable to find a sprite with label <%s>!", label.c_str());
	return NULL;
}
