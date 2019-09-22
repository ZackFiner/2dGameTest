#pragma once
#include "ofMain.h"
class entity;

struct boundingBox
{
	std::vector<glm::vec2> verts;
	float rot;
	glm::vec2 pos;
};

struct AABB
{
	glm::vec2 NW_Corner, SE_Corner;
};

class collisionHull
{
public:
	entity* owner;
	glm::vec2 pos;
	float rot;
	boundingBox getBB();
	AABB getAABB();
};