#pragma once
#include "particleEmitter.h"

/*H*********************************************************
 * FILE: particleEmitter.cpp
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

particleEmitter::particleEmitter(particleSystem * _system) { system = _system; }

void particleEmitter::update() {};

void particleEmitter::setPos(const glm::vec2& pos)
{
	this->pos = pos;
}
glm::vec2 particleEmitter::getPos() const {
	if (getParent() != nullptr)
		return glm::rotate(pos, glm::radians(this->getRot())) + getParent()->getPos();
	return pos;
}
void particleEmitter::setRot(float rot)
{
	this->rot = rot;
}
float particleEmitter::getRot() const
{
	if (getParent() != nullptr)
		return rot + this->getRot();
	return rot;
}
entity* particleEmitter::getParent() const {
	return parent;
}
void particleEmitter::setParent(entity* parent) {
	this->parent = parent;
}

explosionEmitter::explosionEmitter(particleSystem* _system, int particleCount, const glm::vec2& pos) :
	particleEmitter(_system)
{
	for (int i = 0; i < particleCount; i++)
	{
		particle* p = new particle(pos, glm::vec2(), glm::vec2(), 1.0f, ofRandom(1.8)+0.2);
		system->addParticle(p);
	}
	system->addForce((particleForce*)(new impulseForce(10000.0f)));
	system->addForce((particleForce*)(new screenDragForce(20.0f)));
	system->addForce((particleForce*)(new turbulanceForce(glm::vec2(-50.0f,-50.0f), glm::vec2(50.0f, 50.0f))));
}
sparkEmitter::sparkEmitter(particleSystem* _system, int particleCount, const glm::vec2& pos) :
	particleEmitter(_system)
{
	for (int i = 0; i < particleCount; i++)
	{
		particle* p = new particle(pos, glm::vec2(), glm::vec2(), 1.0f, ofRandom(1.8) + 0.2);
		p->dim = glm::vec2(2.0f, 2.0f);
		p->setColor(ofColor::yellow);
		system->addParticle(p);
	}
	system->addForce((particleForce*)(new impulseForce(10000.0f)));
	system->addForce((particleForce*)(new screenDragForce(20.0f)));
	system->addForce((particleForce*)(new turbulanceForce(glm::vec2(-50.0f, -50.0f), glm::vec2(50.0f, 50.0f))));
}