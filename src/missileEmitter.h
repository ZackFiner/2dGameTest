#pragma once
#include "ofMain.h"
#include "solidEntity.h"
/*H**********************************************************************
 * FILENAME: missileEmitter.h
 * AUTHOR: Zackary Finer
 * DATE: 11/1/2019
 *
 * DESCRIPTION:
 * Missile Emitters are closer to particle emitters than they are to sprite
 * emitters: They are responsible for integrating the motion of their
 * emitted entities, as well as managing them.
 * 
 * This file contains implementations/definitions of all classes associated
 * with the missile emitters.
 *
 ************************************************************************/

class missileEmitter
{

};

class integratedMissile : public solidEntity
{

};

class missileForce
{

};

class missileFallForce : public missileForce
{

};