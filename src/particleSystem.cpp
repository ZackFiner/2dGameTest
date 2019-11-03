#include "particleSystem.h"
#include "particle.h"
#include "GameSettings.h"
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

particleSysStaticStuff& sysStatic()
{
	static particleSysStaticStuff* particle_static_resource = new particleSysStaticStuff();
	return *particle_static_resource;
}


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
			}
		}
	}
	firstApp = false;
	for (auto p : particles)
	{
		p->integrate();
	}

	for (auto new_part : spawnedParts)
	{
		particles.push_back(new_part);
	}
	spawnedParts.clear();
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

void particleSystem::initSoundPlay(ofSoundPlayer* _initSound)
{
	initSound = _initSound;
	initSound->play();
}

impulseForce::impulseForce(float _strength)
{
	strength = _strength;
}

void impulseForce::updateParticle(particle* p) const
{
	glm::vec2 dir = glm::circularRand(1.0f);
	p->force += dir * (ofRandom(strength*0.2)+strength*0.8);
}
bool impulseForce::applyOnce() const { return true; }

turbulanceForce::turbulanceForce(const glm::vec2& _min, const glm::vec2& _max)
{
	min = _min;
	max = _max;
}
void turbulanceForce::updateParticle(particle* p) const
{
	glm::vec2 dir = glm::vec2(ofRandom(max.x-min.x)+min.x, ofRandom(max.y-min.y)+min.y);
	p->force += dir;
}
bool turbulanceForce::applyOnce() const { return false; }

screenDragForce::screenDragForce(float spd) { speed = spd; }
void screenDragForce::updateParticle(particle* p) const {
	p->force += glm::vec2(0, -speed);
}
bool screenDragForce::applyOnce() const { return false; }

trailForce::trailForce(const glm::vec2& o, const glm::vec2& d, float r, float magm, float magM)
{
	mag_max = magM;
	mag_min = magm;
	origin = o;
	dir = d;
	radius = r;

}

void trailForce::updateParticle(particle* particle) const {
	glm::vec2 p_dir = glm::rotate(dir, glm::radians(ofRandomf()*radius));
	float mag = ofRandom(mag_max - mag_min) + mag_min;
	particle->force += p_dir * mag;
}
bool trailForce::applyOnce() const { return false; }


washForce::washForce(const glm::vec2& o, float magm, float magM)
{
	mag_max = magM;
	mag_min = magm;
	origin = o;

}

void washForce::updateParticle(particle* particle) const {
	glm::vec2 dir = glm::normalize(particle->getPos() - origin);
	float mag = ofRandom(mag_max - mag_min) + mag_min;
	particle->force += dir * mag;
}
bool washForce::applyOnce() const { return false; }

projectileForce::projectileForce(const glm::vec2& _dir, float _spd)
{
	dir = _dir;
	spd = _spd;
}

void projectileForce::updateParticle(particle* particle) const
{
	particle->force += dir * spd;
}

bool projectileForce::applyOnce() const
{
	return true;
}

void dragForce::updateParticle(particle* particle) const
{
	particle->force += particle->getAcc()*-PARTICLE_DRAG;
}
bool dragForce::applyOnce() const
{
	return false;

}

spreadForce::spreadForce(float _amnt)
{
	amnt = _amnt;
}
void spreadForce::updateParticle(particle* particle) const
{
	particle->force += glm::vec2(glm::ballRand(amnt));
}
bool spreadForce::applyOnce() const
{
	return true;
}