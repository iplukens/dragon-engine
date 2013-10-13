#include <string>
#include <map>
#include <iostream>
#include <fstream>

//Engine includes
#include "LogManager.h"

//Game includes
#include "LevelManager.h"
#include "MazePiece.h"
#include "HealthPickup.h"
#include "Hero.h"
#include "Monster.h"

using std::string;
using std::map;
using std::ifstream;

//Return true if string only contains spaces
bool has_only_spaces(const string& str) {
	return str.find_first_not_of (' ') == str.npos;
}

bool is_comment(const string& str) {
	return str[0] == '/' && str[1] == '/';
}

//Convert character and position to the correct class, and create it
void convertObject(char object, Position pos){
	LogManager &log_manager = LogManager::getInstance();

	switch(object){
	//Wall
	case '#':
		new MazePiece(pos);
		break;

		//Hero
	case 'H':
		new Hero(pos);
		break;

		//Monster
	case 'M':
		new Monster(pos);
		break;

		//Health Pickup
	case '+':
		new HealthPickup(pos);
		break;

		//Ignore space and newlines and null terminators
	case '\n':
		break;
	case '\0':
		break;
	case ' ':
		break;

		//Unknown character
	default:
		log_manager.writeLog("LevelManager::loadLevel() Error! Undefined character of <%c> used!", object);
		break;
	}
}

//Read single line of form 'tag number', and skip or create pieces as needed
void readLine(ifstream *p_file, int *p_line_number){
	LogManager &log_manager = LogManager::getInstance();
	string line;

	getline(*p_file, line);

	//DiscardCR
	if (line[line.size()-1] == '\r'){
		line.erase(line.size()-1);
	}

	//Leave if blank line or is a comment
	if (!(has_only_spaces(line) || is_comment(line))){

		//Loop through each character
		for(int i = 0; i < line.size(); i++){
			//Position of the character/object
			Position pos(i, (*p_line_number) + VIEW_OBJECT_OFFSET);

			convertObject(line[i], pos);
		}

		(*p_line_number)++;
	}
}

LevelManager::LevelManager(){
	level_count = 0;
}

int LevelManager::startUp(){
	return 0;
}

void LevelManager::shutDown(){
}

int LevelManager::prepareLevel(string filename, string label){

	//If already exists, return error
	if (levels.count(label)){
		return 1;
	}

	//Else save map
	levels[label, filename];

	return 0;
}

int LevelManager::removePreparedLevel(string label){

	int num_erased = levels.erase(label);

	//If we didn't erase anything, return error
	if (num_erased == 0){
		return 1;
	} else {
		return 0;
	}
}

bool LevelManager::loadLevel(string label){
	LogManager &log_manager = LogManager::getInstance();
	log_manager.writeLog("LevelManager::loadLevel() attempting to load level with label <%s>", label.c_str());

	if (!levels.count(label)){
		//We don't have the level loaded
		log_manager.writeLog("LevelManager::loadLevel() encountered an error! No level pre-loaded with label <%s>!", label.c_str());
		return false;
	}

	string filename = levels[label];
	ifstream levelFile(filename.c_str());
	int lineNumber = 0;

	while (levelFile.is_open()){
		readLine(&levelFile, &lineNumber);
	}

	if (lineNumber == 0){
		//No lines read, level loading failed
		return false;
	}

	return true;
}
