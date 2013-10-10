/*
 * ObjectListIterator.h
 *
 *  Created on: Sep 14, 2013
 *      Author: ian
 */

#ifndef __OBJECTLISTITERATOR_H_
#define __OBJECTLISTITERATOR_H_

#include "ObjectList.h"
class ObjectList;
class ObjectListIterator {
private:
	ObjectListIterator(); // Must be given list when created.
	int index; // Index into list.
	const ObjectList *p_list; // List iterating over.
public:
	~ObjectListIterator();
// Create iterator, over indicated list.
	ObjectListIterator(const ObjectList *p_l);
	void first(); // Set iterator to first item in list.
	void next(); // Set iterator to next item in list.
	bool isDone(); // Return true if at end of list.
	int getIndex(); // Return the current index of the item
// Return pointer to current Object, NULL if done/empty.
	Object *currentObject();
};

#endif /* OBJECTLISTITERATOR_H_ */
