#include "motionPath.h"

/*H******************************************************************
 * FILENAME: motionPath.cpp
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 *
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