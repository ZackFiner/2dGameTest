#pragma once
#include "ofMain.h"

#define STEP_SIZE 0.1f
#define VERTICAL_MOVEMENT 40.0f

/*H******************************************************************
 * FILENAME: motionPath.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * MotionPath provides an interface which can be implemented to define
 * a parametric path along which an object can travel. This file also
 * contains a few concrete implementations of the motion path method.
 * 
 * These paths are used by enemy sprites to determine their path of
 * travel.
 *
 ********************************************************************/

class motionPath
{
public:
	virtual glm::vec2 getPos(float time) const = 0;
	virtual float getRot(float time) const = 0;
};

class sinPath : public motionPath
{
	bool left;
	float period, phase, amplitude, spd;
	glm::vec2 start;
public:
	sinPath(float _period, float _phase, float _amplitude, float _spd, const glm::vec2& _start, bool _left);
	glm::vec2 getPos(float time) const;
	float getRot(float time) const;
};

class linearPath : public motionPath
{
	glm::vec2 start;
	glm::vec2 heading;
	float spd;
public:
	linearPath(const glm::vec2& _start, const glm::vec2& _heading, float _spd);
	glm::vec2 getPos(float time) const;
	float getRot(float time) const;
};