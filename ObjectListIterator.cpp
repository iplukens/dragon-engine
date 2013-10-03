/*
 * ObjectListIterator.cpp
 *
 *  Created on: Sep 14, 2013
 *      Author: ian
 */

#include "ObjectListIterator.h"

//  never called; added initialize lines to suppress compiler warnings
ObjectListIterator::ObjectListIterator() {
	index = 0;
	p_list = 0;
}

ObjectListIterator::~ObjectListIterator() {
	// TODO Auto-generated destructor stub
}

// actual constructor
ObjectListIterator::ObjectListIterator(const ObjectList *p_l){
	index = 0;
	p_list = p_l;
}

int ObjectListIterator::getIndex(){
	return index;
}

void ObjectListIterator::first(){
	index = 0;// Set iterator to first item in list.
}
void ObjectListIterator::next(){
	index++; // Set iterator to next item in list.
}
bool ObjectListIterator::isDone(){
	return index >= p_list->count;// Return true if at end of list.
}

// Return pointer to current Object, NULL if done/empty.
Object* ObjectListIterator::currentObject(){
	return p_list->list[index];
}

