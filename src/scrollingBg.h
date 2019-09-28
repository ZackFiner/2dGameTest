#pragma once
#include "ofMain.h"
class scrollingBg
{
	ofImage tile1, tile2;
	glm::vec2 pos;
	float speed;
public:
	scrollingBg(const std::string&, float);
	void draw() const;
	void update();
	void setSpeed(float);
};