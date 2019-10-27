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
class particle
{
protected:
	glm::vec2 pos, vel, acc;
	float mass;
	ofColor col = ofColor::red;
	float lifetime;
	float age=0.0f;
public:
	glm::vec2 dim = glm::vec2(5.0f, 5.0f);
	glm::vec2 force;
	particle(const glm::vec2& _pos, const glm::vec2& _vel, const glm::vec2& _acc, float _mass, float _lifetime);
	particle(const glm::vec2& _pos, float _lifetime);
	void setMass(float _mass);
	void setColor(const ofColor& _col);
	ofColor getColor() const;
	float getAge() const;
	float getLifetime() const;

	virtual void integrate();
	virtual void draw() const;
	virtual ~particle();
};