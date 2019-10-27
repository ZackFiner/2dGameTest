#pragma once
#include "ofMain.h"
/*H*********************************************************
 * FILE: particleSystem.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * Description:
 * This class contains the implementation of the particle
 * system class (a class which is responsible for managing)
 * all particles with a specific set of forces applied to them
 * as well as the particle force interface with a few concrete
 * implementations of particle forces.
 *
 ***********************************************************/

class particle;

class particleForce
{
	public:
		virtual void updateParticle(particle* particle) const = 0;
		virtual bool applyOnce() const = 0;
};

class particleSystem
{
private:
	std::vector<particle*> particles;
	std::vector<particleForce*> forces;
	float lifeTime = -1.0f;
	float age = 0;
	bool firstApp = true;
public:
	particleSystem();
	void update();
	void addForce(particleForce*);
	void addParticle(particle*);
	void clear();
	void setLifetime(float);

	void draw() const;
	int getCount() const;
	float getLifeTime() const;
	float getAge() const;
	particleForce* getForce(int index) const;
	~particleSystem();

};

class impulseForce : particleForce
{
private:
	float strength;
public:
	impulseForce(float);
	void updateParticle(particle* particle) const;
	bool applyOnce() const;
};

class turbulanceForce : particleForce
{
private:
	glm::vec2 min, max;
public:
	turbulanceForce(const glm::vec2&, const glm::vec2&);
	void updateParticle(particle* particle) const;
	bool applyOnce() const;
};

class screenDragForce : particleForce
{
private:
	float speed;
public:
	screenDragForce(float);
	void updateParticle(particle* particle) const;
	bool applyOnce() const;
};