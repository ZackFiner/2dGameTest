#pragma once
#include "ofMain.h"
struct boundingBox
{
	std::vector<glm::vec2> verts;
	float rot;
	glm::vec2 pos;
};

class collisionHull
{
public:
	glm::vec2 pos;
	float rot;
	boundingBox getBB();
	boundingBox getAABB();
};