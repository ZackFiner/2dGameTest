#pragma once
#include "entity.h"
#include "ofMain.h"
#include "particleSystem.h"
#include "particle.h"
/*H*********************************************************
 * FILE: particleEmitter.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * Description:
 * This class contains the definition for a particle emitter
 * interface, as well as a few concrete implementations
 * of particle emitters.
 *
 * Particle Emitters are responsible for the systematic creation
 * of particles.
 *
 ***********************************************************/
class particleEmitter
{
protected:
	entity* parent = nullptr;
	glm::vec2 pos;
	float rot;
	particleSystem* system;
public:
	particleEmitter(particleSystem* _system);
	virtual void update();
	virtual void setPos(const glm::vec2&);
	virtual glm::vec2 getPos() const;
	virtual void setRot(float);
	virtual float getRot() const;
	virtual entity* getParent() const;
	virtual void setParent(entity*);
};
class explosionEmitter : public particleEmitter
{
public:
	explosionEmitter(particleSystem* _system, int particleCount, const glm::vec2& pos);
};
class sparkEmitter : public particleEmitter
{
public:
	sparkEmitter(particleSystem* _system, int particleCount, const glm::vec2& pos);
};

class smokeEmitter : public particleEmitter
{
	trailForce* force;
	bool started = false;
	float minF = 0.05f;
	float maxF = 0.1f;
	float freq;
	unsigned long lastEmit=0;
public:
	ofColor smokeColor = ofColor::white;
	smokeEmitter(particleSystem* _system, entity* _parent);
	void start();
	void update();
	void stop();
};

class washEmitter : public particleEmitter
{
	washForce* force;
	bool started = false;
	float freq;
	unsigned long lastEmit = 0;
public:
	float minF = 0.05f;
	float maxF = 0.1f;
	ofColor smokeColor = ofColor::white;
	washEmitter(particleSystem* _system, entity* _parent);
	void start();
	void update();
	void stop();
};