#pragma once
#include "entityManager.h"
#include "entity.h"

/*H**********************************************************************
 * FILENAME: emitter.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * Emitters are a type of entity which creates other entities in a
 * systematic way.
 *
 * Examples include:
 * > explosions are composed of different sprite entities
 *   which travel outward from an origin and fade out of existance
 *
 * > guns or rocket launchers creat missile entities that fly forward and
 *   hit some target. 
 *
 * Emitters usually are not drawn, so this class implements the draw
 * method to not do anything.
 *
 ************************************************************************/

class emitter : public entity
{
protected:
public:
	emitter(entityManager*);
	void draw();
};