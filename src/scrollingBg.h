#pragma once
#include "ofMain.h"
/*H******************************************************************
 * FILENAME: scrollingBg.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * scrollingBg is used to display scrolling background images, such
 * as those used for level terrain. Right now it only supports
 * vertical scrolling.
 *
 ********************************************************************/
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