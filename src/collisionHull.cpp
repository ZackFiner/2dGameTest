#include "collisionHull.h"
#include "entity.h"
#include <limits>

/*H******************************************************************
 * FILENAME: collisionHull.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * This file contains definitions for the collisionHull class, which
 * is used to reprsent a collision hull or hitbox for a given object.
 * it also include declerations for periphreal helper classes like
 * AABB (axis-aligned bounding box) and regular bounding boxes.
 */
boundingBox::boundingBox()
{
	verts.push_back(glm::vec2(-DEFAULT_BOX_SIZE / 2, -DEFAULT_BOX_SIZE / 2));
	verts.push_back(glm::vec2(-DEFAULT_BOX_SIZE / 2, DEFAULT_BOX_SIZE / 2));
	verts.push_back(glm::vec2(DEFAULT_BOX_SIZE / 2, DEFAULT_BOX_SIZE / 2));
	verts.push_back(glm::vec2(DEFAULT_BOX_SIZE / 2, -DEFAULT_BOX_SIZE / 2));
	rot = 0.0f;
	pos = glm::vec2(0.0f, 0.0f);
}

boundingBox::boundingBox(const glm::vec2& v0, const glm::vec2& v1, const glm::vec2& v2, const glm::vec2& v3)
{
	verts.push_back(v0);
	verts.push_back(v1);
	verts.push_back(v2);
	verts.push_back(v3);
	rot = 0.0f;
	pos = glm::vec2(0.0f, 0.0f);
}
boundingBox boundingBox::getSquare(float size)
{
	boundingBox square;
	square.verts.push_back(glm::vec2(-size / 2, -size / 2));
	square.verts.push_back(glm::vec2(-size / 2, size / 2));
	square.verts.push_back(glm::vec2(size / 2, size / 2));
	square.verts.push_back(glm::vec2(size / 2, -size / 2));
	square.rot = 0.0f;
	square.pos = glm::vec2(0.0f, 0.0f);
	return square;
}

std::vector<glm::vec2> boundingBox::getTransformed(const glm::vec2& _pos, float _rot)
{
	float theta = glm::radians(_rot);
	glm::mat2 rot_m = glm::mat2(glm::vec2(glm::cos(theta), glm::sin(theta)), glm::vec2(-glm::sin(theta), glm::cos(theta)));
	std::vector<glm::vec2> newVerts;
	for (auto vert : verts)
	{
		newVerts.push_back(vert*rot_m + _pos);
	}
	return newVerts;
}

AABB::AABB() : 
	NW_Corner(glm::vec2(0.0f,0.0f)),
	SE_Corner(glm::vec2(0.0f, 0.0f))
{

}
AABB::AABB(const glm::vec2& v1, const glm::vec2& v2) :
	NW_Corner(v1),
	SE_Corner(v2)
{

}
AABB::AABB(const AABB& o) :
	NW_Corner(o.NW_Corner),
	SE_Corner(o.SE_Corner)
{

}

glm::vec2 collisionHull::getPos()
{
	return owner->getPos() + pos;
}

float collisionHull::getRot()
{
	return owner -> getRot() + rot;
}

bool collisionHull::wasModified()
{
	return changed;
}

boundingBox collisionHull::getBB()
{
	return bb;
}
void collisionHull::updateAABB()
{
	boundingBox bb = getBB();
	auto t_verts = bb.getTransformed(getPos(), getRot());
	glm::vec2 max = t_verts[0], min = t_verts[0];

	for (auto vert : t_verts)
	{
		if (vert.x <= min.x) min.x = vert.x;
		if (vert.x >= max.x) max.x = vert.x;
		if (vert.y <= min.y) min.y = vert.y;
		if (vert.y >= max.y) max.y = vert.y;
	}
	last_val = AABB(max, min);
}
AABB collisionHull::getAABB()
{
	if (wasModified()) // we will update only when the rotation or position has changed
	{
		updateAABB();
		updateRadius();
		changed = false;
	}
	return last_val;

}

void collisionHull::updateRadius()
{
	float sqrDst = FLT_MIN;
	auto t_verts = getBB().verts;
	for (auto p : t_verts)
	{
		auto dist = glm::dot(p,p);
		if (sqrDst < dist)
			sqrDst = dist;
	}
	radius_last = glm::sqrt(glm::max(0.0f, sqrDst));
}

float collisionHull::getRadius()
{
	if (wasModified())
	{
		updateAABB();
		updateRadius();
		changed = false;
	}
	return radius_last;
}

float collisionHull::getSweptRadius()
{
	if (owner != nullptr)
		return getRadius() + glm::fastLength(owner->getVelocity());
	return getRadius();
}


void collisionHull::debugDrawAABB()
{
	ofNoFill();
	glm::vec2 dim = last_val.NW_Corner - last_val.SE_Corner;
	ofDrawRectangle(last_val.SE_Corner, dim.x, dim.y);
	ofFill();
}

void collisionHull::setBB(const glm::vec2& v0, const glm::vec2& v1, const glm::vec2& v2, const glm::vec2& v3)
{
	bb = boundingBox(v0, v1, v2, v3);
}