#include "particle.h"
/*H*********************************************************
 * FILE: particle.cpp
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

particle::particle(const glm::vec2& _pos, const glm::vec2& _vel, const glm::vec2& _acc, float _mass, float _lifetime)
{
	pos = _pos;
	vel = _vel;
	acc = _acc;
	mass = _mass;
	lifetime = _lifetime;
}

particle::particle(const glm::vec2& _pos, float _lifetime) :
	particle(_pos, glm::vec2(), glm::vec2(), 10.0f, _lifetime)
{}

void particle::setMass(float _mass)
{
	mass = _mass;
}

void particle::setColor(const ofColor& _col)
{
	col = _col;
}
ofColor particle::getColor() const
{
	return col;
}

void particle::integrate()
{
	// a = F/m
	float dt = ofGetLastFrameTime();
	acc += force * (1.0f / mass);
	vel += acc * dt;
	vel *= PARTICLE_DAMPENING;
	pos += vel * dt;

	age += dt;
	force = glm::vec2();
}

void particle::draw() const
{
	ofPushMatrix();
		ofTranslate(pos-dim/2);
		ofSetColor(col);
		ofDrawRectangle(glm::vec2(), dim.x, dim.y);
		ofSetColor(ofColor::white);
	ofPopMatrix();
}

float particle::getAge() const { return age; }
float particle::getLifetime() const{ return lifetime; }

particle::~particle() {}