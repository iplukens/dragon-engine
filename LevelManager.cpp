#include <string>
#include <map>

#include "LevelManager.h"

using std::string;
using std::map;

LevelManager::LevelManager(){
	level_count = 0;
}

int LevelManager::startUp(){
	is_started = true;
	return 0;
}

void LevelManager::shutDown(){
	is_started = false;
}

int LevelManager::prepareLevel(string filename, string label){

	//If already exists, return error
	if (levels.count(label)){
		return 1;
	}

	//Else save map
	levels.insert(label, filename);

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

	if (!levels.count(label)){
		//We don't have the level loaded
		return false;
	}

	string filename = levels[label];

}
