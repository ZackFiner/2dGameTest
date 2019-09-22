#pragma once
#include "ofMain.h"
class entity;
struct boundingBox
{
	std::vector<glm::vec2> verts;
	float rot;
	glm::vec2 pos;
};

class collisionHull
{
public:
	entity* owner;
	glm::vec2 pos;
	float rot;
	boundingBox getBB();
	boundingBox getAABB();
};