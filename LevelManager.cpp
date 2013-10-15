#include <string>
#include <map>
#include <list>
#include <iostream>
#include <fstream>

//Engine includes
#include "LogManager.h"
#include "ViewObject.h"
#include "GameManager.h"

//Game includes
#include "LevelManager.h"
#include "MazePiece.h"
#include "HealthPickup.h"
#include "PointsPickup.h"
#include "Hero.h"
#include "Monster.h"
#include "Ghost.h"
#include "Points.h"
#include "MaxHealthPickup.h"
#include "RapidFire.h"
#include "Exit.h"
#include "Monster2.h"

using std::string;
using std::map;
using std::list;
using std::ifstream;

//Return true if string only contains spaces
bool has_only_spaces(const string& str) {
	return str.find_first_not_of(' ') == str.npos;
}

bool is_comment(const string& str) {
	return str[0] == '/' && str[1] == '/';
}

//Convert character and position to the correct class, and create it
void convertObject(char object, Position pos, ObjectList* list) {
	LogManager &log_manager = LogManager::getInstance();

	switch (object) {
	//Wall
	case '#':
		log_manager.writeLog(
				"LevelManager::loadLevel() is creating a MazePiece at Position <%d, %d>",
				pos.getX(), pos.getY());
		list->insert(new MazePiece(pos));
		break;

		//Hero
	case 'H':
		log_manager.writeLog(
				"LevelManager::loadLevel() is creating a Hero at Position <%d, %d>",
				pos.getX(), pos.getY());
		list->insert(new Hero(pos));
		break;

		//Monster
	case 'M':
		log_manager.writeLog(
				"LevelManager::loadLevel() is creating a Monster at Position <%d, %d>",
				pos.getX(), pos.getY());
		list->insert(new Monster(pos));
		break;

		//Monster2
	case 'm':
		log_manager.writeLog(
				"LevelManager::loadLevel() is creating a Monster2 at Position <%d, %d>",
				pos.getX(), pos.getY());
		list->insert(new Monster2(pos));
		break;

		//Ghost
	case 'G':
		log_manager.writeLog(
				"LevelManager::loadLevel() is creating a Ghost at Position <%d, %d>",
				pos.getX(), pos.getY());
		list->insert(new Ghost(pos));
		break;

		//Health Pickup
	case '+':
		log_manager.writeLog(
				"LevelManager::loadLevel() is creating a Health Pickup at Position <%d, %d>",
				pos.getX(), pos.getY());
		list->insert(new HealthPickup(pos));
		break;

		// points pickup
	case '*':
		log_manager.writeLog(
				"LevelManager::loadLevel() is creating a Points Pickup at Position <%d, %d>",
				pos.getX(), pos.getY());
		list->insert(new PointsPickup(pos));
		break;

		// max health pickup
	case 'O':
		log_manager.writeLog(
				"LevelManager::loadLevel() is creating a Max Health Pickup at Position <%d, %d>",
				pos.getX(), pos.getY());
		list->insert(new MaxHealthPickup(pos));
		break;

		// rapid fire pickup
	case 'R':
		log_manager.writeLog(
				"LevelManager::loadLevel() is creating a Rapid Fire Pickup at Position <%d, %d>",
				pos.getX(), pos.getY());
		list->insert(new RapidFire(pos));
		break;

	case 'E':
		log_manager.writeLog("LevelManager::loadLevel() is creating an Exit at Position <%d, %d>", pos.getX(), pos.getY());
		list->insert(new Exit(pos));
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
		log_manager.writeLog(
				"LevelManager::loadLevel() Error! Undefined character of <%c> used!",
				object);
		break;
	}
}

//Read single line of form 'tag number', and skip or create pieces as needed
void readLine(ifstream *p_file, int *p_line_number, ObjectList* list) {
	LogManager &log_manager = LogManager::getInstance();
	string line;

	getline(*p_file, line);

	//DiscardCR
	if (line[line.size() - 1] == '\r') {
		line.erase(line.size() - 1);
	}

	//Leave if blank line or is a comment
	if (!(has_only_spaces(line) || is_comment(line))) {

		//Loop through each character
		for (int i = 0; i < line.size(); i++) {
			//Position of the character/object
			Position pos(i, (*p_line_number) + VIEW_OBJECT_OFFSET);

			convertObject(line[i], pos, list);
		}

		(*p_line_number)++;
	}
}

LevelManager::LevelManager() {
	level_count = 0;
}

LevelManager &LevelManager::getInstance() {
	static LevelManager level_manager;
	return level_manager;
}

int LevelManager::startUp() {
	return 0;
}

void LevelManager::shutDown() {
}

int LevelManager::prepareLevel(string filename, string label) {
	LogManager &log_manager = LogManager::getInstance();

	//If already exists, return error
	if (level_files.count(label)) {
		log_manager.writeLog(
				"LevelManager::prepareLevel() failed! A level with a label of <%s> already exists!",
				label.c_str());
		return 1;
	}

	//Else save map
	level_count++;
	log_manager.writeLog(
			"LevelManager::prepareLevel() prepared the level stored in filename <%s> with a label of <%s> and an int of <%d>",
			filename.c_str(), label.c_str(), level_count);
	level_files[label] = filename;
	levels[label] = level_count;
	level_order.push_back(label);

	return 0;
}

int LevelManager::removePreparedLevel(string label) {

	int num_erased = level_files.erase(label);
	num_erased += levels.erase(label);

	//If we didn't erase anything, return error
	if (num_erased == 0) {
		return 1;
	} else {
		level_count--;
		return 0;
	}
}

bool LevelManager::loadLevel(string label) {
	LogManager &log_manager = LogManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
	SceneGraph scene_graph = world_manager.getSceneGraph();

	log_manager.writeLog(
			"LevelManager::loadLevel() attempting to load level with label <%s>",
			label.c_str());

	//Safety check
	if (level_files.count(label) == 0) {
		//We don't have the level loaded
		log_manager.writeLog(
				"LevelManager::loadLevel() encountered an error! No level prepared with label <%s>!",
				label.c_str());
		return false;
	}

	//	//Delete gamestart
	//	if (!world_manager.getAllObjects().isEmpty()){
	//		ObjectListIterator world_it = world_manager.getAllObjects().createIterator();
	//		while(!world_it.isDone()){
	//			if (!(world_it.currentObject()->getType() == POINTS_STRING || world_it.currentObject()->getType() == "Health")){
	//				world_manager.markForDelete(world_it.currentObject());
	//			}
	//
	//			world_it.next();
	//		}
	//	}

	//Old level
	if (!current_level_obj.isEmpty()) {
		ObjectListIterator it = current_level_obj.createIterator();

		while (!it.isDone()) {
			world_manager.markForDelete(it.currentObject());

			it.next();
		}
	}

	log_manager.writeLog(
			"LevelManager::loadLevel() level with label <%s> is represented with <%d>",
			label.c_str(), levels[label]);

	//Prepare World Manager and Scene Graph
	scene_graph.setLevel(1);
	//	if (scene_graph.setLevel(levels[label])){
	//		log_manager.writeLog("LevelManager::loadLevel() encountered an error when calling SceneGraph::setLevel() with an argument of <%d>!", levels[label]);
	//	}

	//Actual load
	string filename = level_files[label];
	ifstream levelFile(filename.c_str());
	int lineNumber = 0;

	while (levelFile.is_open() && levelFile.good()) {
		readLine(&levelFile, &lineNumber, &current_level_obj);
	}

	levelFile.close();

	if (lineNumber == 0) {
		//No lines read, level loading failed
		log_manager.writeLog(
				"LevelManager::loadLevel() failed to load a level! No lines read!");
		return false;
	}

	world_manager.setLevel(1);
	//	if (world_manager.setLevel(levels[label])){
	//		log_manager.writeLog("LevelManager::loadLevel() encountered an error when calling WorldManager::setLevel() with an argument of <%d>!", levels[label]);
	//	}

	log_manager.writeLog(
			"LevelManager::loadLevel() loaded a level with a label of <%s> and with <%d> lines",
			label.c_str(), lineNumber);
	return true;
}

bool LevelManager::nextLevel() {
	if (level_order.empty()) {
		//We are out of levels, it's game over!
		GameManager &game_manager = GameManager::getInstance();
		game_manager.setGameOver(true);

		return false;
	}

	//Load and then delete the first level from the list
	string label = level_order.front();
	level_order.pop_front();

	return loadLevel(label);
}
