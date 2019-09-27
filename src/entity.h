#pragma once
#include "ofMain.h"
#include "EID.h"

class entityManager;
class entity
{
protected:
	EID id; // id initialization is automatic.
	entityManager* manager;
	glm::vec2 position;
	float rot;
	float lifetime = 0.0f;
	float age = 0.0f;
	entity* parent = nullptr;
public:
	entity(entityManager*);
	entity(entityManager*, const glm::vec2&, float);
	entity(const entity&);
	entity& operator=(const entity&);
	EID getID() const;
	float getLifeTime() const;
	float getAge() const;
	void setParent(entity*);
	entity* getParent() const;

	virtual bool hasChanged();
	virtual void draw() = 0;
	virtual ~entity();
	virtual glm::vec2 getPos() const;
	virtual float getRot() const;
	virtual void update();
	virtual void setPos(const glm::vec2&);
	virtual void setRot(float);
	virtual bool isDead() const;
	virtual void setHealth(int);
	virtual glm::vec2 getVelocity() const;

};