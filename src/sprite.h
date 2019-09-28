#pragma once
#include "entity.h"
#include "entityManager.h"
#include "ofMain.h"
/*H******************************************************************
 * FILENAME: sprite.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * I don't know if i want to keep this class, as I feel that entity
 * is a pretty sufficient representation of sprites.
 *
 ********************************************************************/
class sprite : public entity
{
protected:
public:
	sprite(entityManager*);
};