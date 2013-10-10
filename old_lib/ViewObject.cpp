#include <stdio.h>
#include <string.h>

#include "ViewObject.h"
#include "Object.h"
#include "WorldManager.h"
#include "GraphicsManager.h"
#include "EventView.h"
#include "Position.h"
#include "utility.h"

ViewObject::ViewObject(int on_level){

	//Object attributes
	setSolidness(SPECTRAL);
	setAltitude(MAX_ALTITUDE);
	setType("ViewObject");


	//ViewObject attributes
	setValue(0);
	setBorder(true);
	setLocation(TOP_CENTER);
	setColor(COLOR_DEFAULT);

	//Register interest in view events
	registerInterest(VIEW_EVENT);
}

void ViewObject::setValue(int new_value){
	value = new_value;
}

int ViewObject::getValue(){
	return value;
}

void ViewObject::setBorder(bool new_border){
	border = new_border;
}

bool ViewObject::getBorder(){
	return border;
}

void ViewObject::setColor(int new_color){
	color = new_color;
}

int ViewObject::getColor(){
	return color;
}

void ViewObject::setViewString(string new_view_string){
	view_string = new_view_string;
}

string ViewObject::getViewString(){
	return view_string;
}

void ViewObject::setLocation(ViewObjectLocation location){
	WorldManager &world_manager = WorldManager::getInstance();
	Position pos = getPosition();
	int delta = 0;

	switch(location){
	case TOP_LEFT:
		pos.setXY(world_manager.getView().getHorizontal() * 1/6, 1);
		if (getBorder() == false){
			delta = -1;
		}
		break;
	case TOP_CENTER:
		pos.setXY(world_manager.getView().getHorizontal() * 3/6, 1);
		if (getBorder() == false){
			delta = -1;
		}
		break;
	case TOP_RIGHT:
		pos.setXY(world_manager.getView().getHorizontal() * 5/6, 1);
		if(getBorder() == false){
			delta = -1;
		}
		break;
	case BOTTOM_LEFT:
		pos.setXY(world_manager.getView().getHorizontal() * 1/6, world_manager.getView().getVertical()-1);
		if (getBorder() == false){
			delta = 1;
		}
		break;
	case BOTTOM_CENTER:
		pos.setXY(world_manager.getView().getHorizontal() * 3/6, world_manager.getView().getVertical()-1);
		if (getBorder() == false){
			delta = 1;
		}
		break;
	case BOTTOM_RIGHT:
		pos.setXY(world_manager.getView().getHorizontal() * 5/6, world_manager.getView().getVertical()-1);
		if(getBorder() == false){
			delta = 1;
		}
		break;
	}

	pos.setY(pos.getY() + delta);
	setPosition(pos);
}

void ViewObject::draw(){
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	string temp_str;

	if(getBorder() == true){
		temp_str = " " + getViewString() + " " + intToString(value) + " ";
	} else {
		temp_str = getViewString() + " " + intToString(value);
	}

	//Draw centered at position
	Position pos = viewToWorld(getPosition());
	graphics_manager.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());

	//Draw box around display
	if (getBorder() == true){
		int boxLength = strlen(getViewString().c_str()) + 4;
		int boxHeight = 3;
		int boxOffset = boxLength/2;
		bool odd = false;

		if (boxLength % 2){
			odd = true;
		}

		for (int i = 0; i < boxLength; i++){
			Position new_pos(pos.getX() + i - boxOffset, pos.getY()-1);
			graphics_manager.drawCh(new_pos, '-', getColor());
		}

		//Bottom
		for (int i = 0; i < boxLength; i++){
			Position new_pos(pos.getX() + i - boxOffset, pos.getY()+1);
			graphics_manager.drawCh(new_pos, '-', getColor());
		}

		//Left
		Position left_pos(pos.getX()-boxOffset-1, pos.getY());
		graphics_manager.drawCh(left_pos, '|', getColor());

		//Right
		if (!odd){
			Position right_pos(pos.getX()+boxOffset, pos.getY());
			graphics_manager.drawCh(right_pos, '|', getColor());
		} else {
			Position right_pos(pos.getX()+boxOffset+1, pos.getY());
			graphics_manager.drawCh(right_pos, '|', getColor());
		}
	}
}

int ViewObject::eventHandler(Event *p_e){

	//See if this is a ViewEvent
	if (p_e->getType() == VIEW_EVENT){
		EventView *p_ve = (EventView *) p_e;

		//See if event is meant for this object
		if(p_ve->getTag() == getViewString()){

			//Act accoridng if it is a delta or not
			if (p_ve->getDelta()){
				setValue(getValue() + p_ve->getValue());
			} else {
				setValue(p_ve->getValue());
			}
			//Event handled
			return 1;
		}
	}


	//Event not handled
	return 0;
}
