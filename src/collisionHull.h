#pragma once
#include "ofMain.h"

/*H******************************************************************
 * FILENAME: collisionHull.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * This file contains declerations for the collisionHull class, which
 * is used to reprsent a collision hull or hitbox for a given object.
 * it also include declerations for periphreal helper classes like
 * AABB (axis-aligned bounding box) and regular bounding boxes.
 */

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
	float radius_last;
	AABB last_val;
	void updateAABB();
	void updateRadius();
public:
	float getRadius();
	bool changed = true;
	bool wasModified();
	entity* owner;
	glm::vec2 getPos();
	float getRot();
	boundingBox getBB();
	AABB getAABB();
	void debugDrawAABB();
};