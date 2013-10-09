/*
 * Explosion.h
 *
 *  Created on: Sep 4, 2013
 *      Author: ian
 */

#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Object.h"

 class Explosion : public Object {

   protected:
    int time_to_live;
    void step();

   public:
    Explosion();
    int eventHandler(Event *p_e);
  };



#endif /* EXPLOSION_H_ */
