#include "motionPath.h"

/*H******************************************************************
 * FILENAME: motionPath.cpp
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

sinPath::sinPath(float _period, float _phase, float _amplitude, float _spd, const glm::vec2& _start, bool _left)
{
	period = _period;
	phase = _phase;
	amplitude = _amplitude;
	spd = _spd;
	start = _start;
	left = _left;
}

glm::vec2 sinPath::getPos(float time) const
{
	float x = time;
	float y = glm::sin(glm::radians(x)*phase + period)*amplitude;
	return glm::vec2(x * (left ? -1.0f: 1.0f)*spd, y) + start;

}

float sinPath::getRot(float time) const
{
	glm::vec2 lstPos = getPos(time - STEP_SIZE);
	return -glm::orientedAngle(glm::normalize(getPos(time) - lstPos+glm::vec2(0,VERTICAL_MOVEMENT)), glm::vec2(0.0f, 1.0f));
}

linearPath::linearPath(const glm::vec2& _start, const glm::vec2& _heading, float _spd)
{
	start = _start;
	heading = _heading;
	spd = _spd;
}

glm::vec2 linearPath::getPos(float time) const
{
	return start + heading * time*spd;
}

float linearPath::getRot(float time) const
{
	return -glm::orientedAngle(glm::normalize(heading+glm::vec2(0,1.0f)), glm::vec2(0.0f, 1.0f));
}