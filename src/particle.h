#pragma once
#include "ofMain.h"
/*H*********************************************************
 * FILE: particle.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * Description:
 * This class includes the a basic particle class. The class
 * is fairly basic, without any kind of sprite animation.
 * it only displays an image and must be managed by a
 * particle system.
 *
 ***********************************************************/
#define PARTICLE_DAMPENING 0.9f
class particleSystem;
class imageSingleton
{
public:
	ofImage smoke;
	imageSingleton()
	{
		smoke.load("smoke.png");
		smoke.resize(60, 60);
		smoke.mirror(true, false);
	}
};

class particle
{
protected:
	glm::vec2 pos, vel, acc;
	float mass;
	ofColor col = ofColor::red;
	float lifetime;
	float age=0.0f;
public:
	glm::vec2 getPos() const { return pos; }
	glm::vec2 getVel() const { return vel; }
	glm::vec2 getAcc() const { return acc; }
	glm::vec2 dim = glm::vec2(5.0f, 5.0f);
	glm::vec2 force;
	particle(const glm::vec2& _pos, const glm::vec2& _vel, const glm::vec2& _acc, float _mass, float _lifetime);
	particle(const glm::vec2& _pos, float _lifetime);
	void setMass(float _mass);
	void setColor(const ofColor& _col);
	ofColor getColor() const;
	float getAge() const;
	float getLifetime() const;
	float getMass();
	virtual void integrate();
	virtual void draw() const;
	virtual ~particle();
};

class smokeParticle : public particle
{
protected:
	glm::vec2 scale;
	float rot_dir;
	float rot;
	float min_size=1.0f, max_size=5.0f;
public:
	ofColor colOverride = ofColor::white;
	smokeParticle(const glm::vec2& _pos, const glm::vec2& _vel, const glm::vec2& _acc, float _mass, float _lifetime);
	smokeParticle(const glm::vec2& _pos, float _lifetime);
	void setSizeGradient(float min, float max);
	void draw() const;
	void integrate();
};

class smokeStreamer : public smokeParticle
{
	unsigned long lastSpawn=0;
	float trail_density;
	float trail_length;
	particleSystem* sys;
public:
	smokeStreamer(const glm::vec2& _pos, const glm::vec2& _vel, const glm::vec2& _acc, float _mass, float _lifetime, float trail_length, float trail_density, particleSystem* sys);
	smokeStreamer(const glm::vec2& _pos, float _lifetime, float trail_length, float trail_density, particleSystem* sys);
	void integrate();
};