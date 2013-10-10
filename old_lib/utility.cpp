#include <sstream>
#include "utility.h"
#include "WorldManager.h"
#include "LogManager.h"

using std::stringstream;

bool positionsIntersect(Position p1, Position p2){
	return true;
}

bool valueInRange(int value, int min, int max){
	return (min <= value) && (value <= max);
}

//bool boxIntersectsBox(Box box1, Box box2){
//	LogManager &log_manager = LogManager::getInstance();
//
//	int Ax1 = box1.getCorner().getX();
//	int Ax2 = Ax1 + box1.getHorizontal()-1;
//	int Ay1 = box1.getCorner().getY();
//	int Ay2 = Ay1 + box1.getVertical()-1;
//
//	int Bx1 = box2.getCorner().getX();
//	int Bx2 = Bx2 + box2.getHorizontal()-1;
//	int By1 = box2.getCorner().getY();
//	int By2 = By1 + box2.getVertical()-1;
//
//	bool x_overlap = (Bx1 <= Ax1 && Ax1 <= Bx2) || (Ax1 <= Bx1 && Bx1 <= Ax2);
//	bool y_overlap = (By1 <= Ay1 && Ay1 <= By2) || (Ay1 <= By1 && By1 <= Ay2);
//
////	if ((Bx1 <= Ax1 <= Bx2){
////		log_
////	}
//
//	return x_overlap || y_overlap;
//}

bool boxIntersectsBox(Box box1, Box box2) {
	bool x_overlap = (box1.getCorner().getX() <= box2.getCorner().getX()
			<= box1.getCorner().getX() + box1.getHorizontal())
			|| (box2.getCorner().getX() <= box1.getCorner().getX()
					<= box2.getCorner().getX() + box2.getHorizontal());
	bool y_overlap = (box1.getCorner().getY() <= box2.getCorner().getY()
			<= box1.getCorner().getY() + box1.getVertical())
			|| (box2.getCorner().getY() <= box1.getCorner().getY()
					<= box2.getCorner().getY() + box2.getVertical());
	return x_overlap && y_overlap;
}

//Box getWorldBox(Object *p_o){
//	WorldManager &world_manager = WorldManager::getInstance();
//	Box new_object_box;
//	Box world_box = world_manager.getBoundary();
//	Box object_box = p_o->getBox();
//	Position object_pos = worldToView(p_o->getPosition());
//
//	Position new_corner;
//
//	int x, y;
//
//	if (p_o->isCentered()){
//		x =
//	} else {
//
//	}
//	new_corner.setX();
//	new_corner.setY();
//
//	relative_box.setCorner(new_corner);
//	relative_box.setHorizontal(object_box.getHorizontal());
//	relative_box.setVertical(object_box.getVertical());
//
//}

Position worldToView(Position world_pos){
	WorldManager &world_manager = WorldManager::getInstance();
	Position view_pos;

	int x = view_pos.getX() - world_manager.getView().getCorner().getX();
	int y = view_pos.getY() - world_manager.getView().getCorner().getY();

	world_pos.setXY(x, y);

	return world_pos;
}

Position viewToWorld(Position view_pos){
	WorldManager &world_manager = WorldManager::getInstance();
	Position world_pos;

	int x = view_pos.getX() + world_manager.getView().getCorner().getX();
	int y = view_pos.getY() + world_manager.getView().getCorner().getY();

	world_pos.setXY(x, y);

	return world_pos;
}

string intToString(int number){
	//Convert int to string
	stringstream ss;
	ss << number;
	return ss.str();
}
