#include "GraphicsManager.h"
#include "LogManager.h"

#define ERROR_RETURN return -1; log_manager.writeLog("GraphicsManager::startUp() failed!");

GraphicsManager::GraphicsManager(){
	buffer = NULL;
}

GraphicsManager &GraphicsManager::getInstance(){
	static GraphicsManager graphics_manager;
	return graphics_manager;
}

int GraphicsManager::startUp(){
	LogManager& log_manager = LogManager::getInstance();

	if (!is_started){
		if (initscr() == NULL){
			ERROR_RETURN
		}

		buffer = newwin(0,0,0,0);

		if (buffer == NULL){
			ERROR_RETURN
		}

		//Turn on bold for all characters, wAttrOn
		wattron(buffer, A_BOLD);

		//Force redraw
		clearok(buffer, TRUE);

		//Allow cursor to leave window
		leaveok(buffer, TRUE);

		//Enable color
		if (has_colors()){
			start_color();

			init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
			init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
			init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
			init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
			init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
			init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
			init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
		}

		is_started = true;
	}
	log_manager.writeLog("GraphicsManager::startUp() finished successfully");

	return 0;
}

int GraphicsManager::shutDown(){
	if (is_started){
		endwin();

		is_started = false;
	}

	LogManager &log_manager = LogManager::getInstance();
	log_manager.writeLog("GraphicsManager::shutDown() finished successfully");

	return 0;
}

int GraphicsManager::drawCh(Position world_pos, char ch, int color){
	//If using color, turn on color
	wattron(buffer, COLOR_PAIR(color));

	int x = world_pos.getX();
	int y = world_pos.getY();

	//Draw single character at x, y
	mvwaddch(buffer, y, x, ch);

	//If using color, turn off color
	wattroff(buffer, COLOR_PAIR(color));

	return 0;
}

int GraphicsManager::drawString(Position world_pos, string str, Justification just, int color){
	Position starting_pos = world_pos;

	switch(just){
	case CENTER_JUSTIFIED:
		starting_pos.setX(world_pos.getX() - str.size()/2);
		break;
	case RIGHT_JUSTIFIED:
		starting_pos.setX(world_pos.getX() - str.size());
		break;
	case LEFT_JUSTIFIED:
	default:
		break;
	}

	for(int i=0; i < str.size(); i++){
		Position temp_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(temp_pos, str[i], color);
	}

	return 0;
}

int GraphicsManager::drawFrame(Position world_pos, Frame frame, bool centered, int color){
	LogManager& log_manager = LogManager::getInstance();

	if (frame.getString().empty()){
		return -1;
	}

	int x_offset = 0;
	int y_offset = 0;

	if (centered){
		x_offset = frame.getWidth() / 2;
		y_offset = frame.getHeight() / 2;
	}

	string str = frame.getString();

	//Draw character by character
	for (int y = 0; y < frame.getHeight(); y++){
		string temp;
		for (int x = 0 ; x < frame.getWidth(); x++){
			Position temp_pos(world_pos.getX() - x_offset + x, world_pos.getY() - y_offset + y);
			drawCh(temp_pos, str[y * frame.getWidth() + x], color);
			temp += str[y * frame.getWidth() + x];
		}
		temp = "";
	}

	return 0;
}

int GraphicsManager::getHorizontal(){
	int max_y = 0;
	int max_x = 0;

	getmaxyx(stdscr, max_y, max_x);

	return max_x;
}

int GraphicsManager::getVertical(){
	int max_y = 0;
	int max_x = 0;

	getmaxyx(stdscr, max_y, max_x);

	return max_y;
}

int GraphicsManager::swapBuffers(){
	LogManager &log_manager = LogManager::getInstance();
	log_manager.writeLog("GraphicsManager::swapBuffers() called");

	int error = 0;

	error += wrefresh(buffer);
	doupdate();
	error += werase(buffer);

	if (error){
		log_manager.writeLog("GraphicsManager::swapBuffers encountered an error!");
	}

	return error;
}

WINDOW *GraphicsManager::getBuffer(){
	return buffer;
}
