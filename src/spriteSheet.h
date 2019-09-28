#pragma once
#include "ofMain.h"

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