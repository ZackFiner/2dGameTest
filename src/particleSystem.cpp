#include "particleSystem.h"
#include "particle.h"

/*H*********************************************************
 * FILE: particleSystem.cpp
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

particleSystem::particleSystem() {}
particleSystem::~particleSystem()
{
	for (auto p : particles)
		delete p;
	for (auto f : forces)
		delete f;
}
void particleSystem::setLifetime(float _lifetime)
{
	lifeTime = _lifetime;
}

void particleSystem::update()
{
	auto p = particles.begin();
	while (p != particles.end()) // de-allocate dead particles
	{
		if ((*p)->getLifetime() >= 0.0f && (*p)->getAge() > (*p)->getLifetime())
		{
			delete (*p);//delete the particle
			p = particles.erase(p);//remove it from our vector
			continue;
		}
		p++;
	}

	for (auto p : particles) // apply all particle forces
	{
		for (auto f : forces)
		{
			if (!f->applyOnce() || firstApp) {
				f->updateParticle(p);
				firstApp = false;
			}
		}
	}

	for (auto p : particles)
	{
		p->integrate();
	}
	age += ofGetLastFrameTime();
}

void particleSystem::addForce(particleForce* force)
{
	forces.push_back(force);
}

void particleSystem::clear()
{
	for (auto p : particles)
		delete p;
	for (auto f : forces)
		delete f;
}

void particleSystem::addParticle(particle* p)
{
	particles.push_back(p);
}

void particleSystem::draw() const {
	for (auto p : particles)
		p->draw();
}

int particleSystem::getCount() const { return particles.size(); }
float particleSystem::getLifeTime() const { return lifeTime; }
float particleSystem::getAge() const { return age; }
particleForce* particleSystem::getForce(int index) const { return forces[index]; }

impulseForce::impulseForce(float _strength)
{
	strength = _strength;
}

void impulseForce::updateParticle(particle* p) const
{
	glm::vec2 dir = glm::circularRand(1.0f);
	p->force += dir * strength;
}
bool impulseForce::applyOnce() const { return true; }

turbulanceForce::turbulanceForce(const glm::vec2& _min, const glm::vec2& _max)
{
	min = _min;
	max = _max;
}
void turbulanceForce::updateParticle(particle* p) const
{
	glm::vec2 dir = glm::linearRand(min, max);
	p->force += dir;
}
bool turbulanceForce::applyOnce() const { return false; }

screenDragForce::screenDragForce(float spd) { speed = spd; }
void screenDragForce::updateParticle(particle* p) const {
	p->force += glm::vec2(0, -speed);
}
bool screenDragForce::applyOnce() const { return false; }