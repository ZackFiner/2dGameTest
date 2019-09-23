#pragma once
#include "ofMain.h"
#include "entity.h"
#include "collisionHull.h"
#include "collisionManager.h"

class boxSprite : public entity
{
private:
	collisionManager * hit_manager;
	collisionHull * hitBox;
	bool changed;
	float size;
public:
	boxSprite(entityManager*, float, collisionManager*);
	void draw();
	bool hasChanged();
	void setPos(const glm::vec2&);
	void setRot(float);
	~boxSprite();
};