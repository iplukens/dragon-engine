/*
 * ObjectList.h
 *
 *  Created on: Sep 14, 2013
 *      Author: ian
 */

#ifndef __OBJECTLIST_H_
#define __OBJECTLIST_H_

#define MAX_OBJECTS 5000
#include "Object.h"
#include "ObjectListIterator.h"

class ObjectListIterator;

class ObjectList {
private:
	int count; // Count of objects in list.
	Object *list[MAX_OBJECTS]; // Array of pointers to objects.
public:
	friend class ObjectListIterator;
	ObjectListIterator createIterator() const;
	ObjectList();
	~ObjectList();

// Insert object pointer in list.
// Return 0 if ok, else -1.
	int insert(Object *p_o);

// Remove object pointer from list.
// Return 0 if found, else -1.
	int remove(Object *p_o);

// Clear list (setting count to 0).
	void clear();

// Return count of number of objects in list.
	int getCount();

// Return true if list is empty, else false.
	bool isEmpty();

// Return true if list is full, else false.
	bool isFull();

// return true if list contains the object
	bool contains(Object *p_o);
};
#endif /* OBJECTLIST_H_ */
