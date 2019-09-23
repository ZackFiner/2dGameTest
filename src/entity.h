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
public:
	entity(entityManager*);
	entity(entityManager*, const glm::vec2&, float);
	entity(const entity&);
	entity& operator=(const entity&);
	EID getID() const;

	virtual bool hasChanged();
	virtual void draw() = 0;
	virtual ~entity();
	virtual glm::vec2 getPos() const;
	virtual float getRot() const;
	virtual void setPos(const glm::vec2&);
	virtual void setRot(float);
};