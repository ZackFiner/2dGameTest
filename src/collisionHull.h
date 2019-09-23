#pragma once
#include "ofMain.h"
class entity;

struct boundingBox
{
	static boundingBox getSquare(float);
	std::vector<glm::vec2> verts;
	float rot;
	glm::vec2 pos;
	std::vector<glm::vec2> getTransformed(const glm::vec2&, float);
};

struct AABB
{
	glm::vec2 NW_Corner, SE_Corner;
	AABB();
	AABB(const glm::vec2&, const glm::vec2&);
	AABB(const AABB&);
};

class collisionHull
{
	glm::vec2 pos;
	float rot;
	AABB last_val;
public:
	bool changed = true;
	bool wasModified();
	entity* owner;
	glm::vec2 getPos();
	float getRot();
	boundingBox getBB();
	AABB getAABB();
	void debugDrawAABB();
};