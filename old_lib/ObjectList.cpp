/*
 * ObjectList.cpp
 *
 *  Created on: Sep 14, 2013
 *      Author: ian
 */

#include "ObjectList.h"

ObjectList::ObjectList() {
	count = 0; // Count of objects in list.
	// Object *list[MAX_OBJECTS];
}

ObjectList::~ObjectList() {
	// TODO Auto-generated destructor stub
}

// Insert object pointer in list.
// Return 0 if ok, else -1.
int ObjectList::insert(Object *p_o) {
	if (count < MAX_OBJECTS) {
		list[count] = p_o;
		count++;
		return 0;
	} else {
		return -1;
	}
}

// create iterator
ObjectListIterator ObjectList::createIterator() const {
	ObjectListIterator oli(this);
	return oli;
}

// Remove object pointer from list.
// Return 0 if found, else -1.
int ObjectList::remove(Object *p_o) {
	ObjectListIterator oli = createIterator();
	while (!oli.isDone()) {
		if (oli.currentObject() == p_o) {
			int start = oli.getIndex();
			count--;
			for (int i = start; i < count; i++) {
				list[i] = list[i + 1];
			}
			return 0;
		}
		oli.next();
	}
	return -1;
}

// Clear list (setting count to 0).
void ObjectList::clear() {
	count = 0;
}

// Return count of number of objects in list.
int ObjectList::getCount() {
	return count;
}

// Return true if list is empty, else false.
bool ObjectList::isEmpty() {
	return count == 0;
}

// Return true if list is full, else false.
bool ObjectList::isFull() {
	return count == MAX_OBJECTS;
}

// Return true if list contains the object
bool ObjectList::contains(Object *p_o) {
	ObjectListIterator li(this);
	for (li.first(); not li.isDone(); li.next()) {
		if (p_o == li.currentObject()) {
			return true;
		}
	}
	return false;
}
