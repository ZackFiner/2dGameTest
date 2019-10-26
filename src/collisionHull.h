#pragma once
#include "ofMain.h"

/*H******************************************************************
 * FILENAME: collisionHull.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * This file contains declerations for the collisionHull class, which
 * is used to reprsent a collision hull or hitbox for a given object.
 * it also include declerations for periphreal helper classes like
 * AABB (axis-aligned bounding box) and regular bounding boxes.
 *
 *********************************************************************/
#define DEFAULT_BOX_SIZE 50.0f
class entity;

struct boundingBox
{
	static boundingBox getSquare(float);
	std::vector<glm::vec2> verts;
	float rot;
	glm::vec2 pos;
	std::vector<glm::vec2> getTransformed(const glm::vec2&, float);
	boundingBox(const glm::vec2&, const glm::vec2&, const glm::vec2&, const glm::vec2&);
	boundingBox();
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
	boundingBox bb;
public:
	float getRadius();
	float getSweptRadius();
	bool changed = true;
	bool wasModified();
	void setBB(const glm::vec2&, const glm::vec2&, const glm::vec2&, const glm::vec2&);
	entity* owner = nullptr;
	glm::vec2 getPos();
	float getRot();
	boundingBox getBB();
	AABB getAABB();
	void debugDrawAABB();
};