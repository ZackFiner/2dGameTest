#pragma once
#include "ofMain.h"
/*H******************************************************************
 * FILENAME: spriteSheet.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * spriteSheet is a class which can be used to draw animated sprites
 * using a spriteSheet. It is currently used by the helicopter class
 * to draw the spinning rotor blades.
 *
 ********************************************************************/
class spriteSheet
{
	ofImage sheet;
	float frequency;
	int curFrame = 0, frameCount;
	long lstF=0.0;
	glm::vec2 dim;
	glm::vec2 frameSize;
	glm::vec2 adj;
public:
	spriteSheet(const std::string&, float, const glm::vec2&, const glm::vec2&, int);
	void update();
	glm::vec2 getSize();
	void draw(const glm::vec2&) const;
};