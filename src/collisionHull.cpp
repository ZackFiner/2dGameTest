#include "collisionHull.h"
#include "entity.h"
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
	return boundingBox::getSquare(10.0f);
}

AABB collisionHull::getAABB()
{
	if (wasModified()) // we will update only when the rotation or position has changed
	{
		boundingBox bb = getBB();
		auto testVal = owner->getPos(); // FIX ME: this returns 0,0 
		std::cout << testVal << std::endl;
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
		changed = false;
	}
	return last_val;

}

void collisionHull::debugDrawAABB()
{
	ofNoFill();
	glm::vec2 dim = last_val.NW_Corner - last_val.SE_Corner;
	ofDrawRectangle(last_val.NW_Corner, dim.x, dim.y);
	ofFill();
}
