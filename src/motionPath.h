#pragma once
#include "ofMain.h"

#define STEP_SIZE 0.1f
#define VERTICAL_MOVEMENT 40.0f

/*H******************************************************************
 * FILENAME: motionPath.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 *
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