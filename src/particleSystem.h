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

class particleSysStaticStuff
{
public:
	ofSoundPlayer explosion1;
	ofSoundPlayer explosion2;
	ofSoundPlayer explosion3;
	particleSysStaticStuff() {
		explosion1.load("Explosion01.wav");
		explosion1.setVolume(0.2);
		explosion2.load("Explosion02.wav");
		explosion2.setVolume(0.2);
		explosion3.load("Explosion03.wav");
		explosion3.setVolume(0.2);
	}
	ofSoundPlayer& getRandomExplosion()
	{
		int selector = (int)(ofRandom(4));
		switch (selector)
		{
			case 0:
				return explosion1;
			case 1:
				return explosion2;
			default:
				return explosion3;
		}

	}
};
particleSysStaticStuff& sysStatic();
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
	float lifeTime = -1.0f;
	float age = 0;
	bool firstApp = true;
	ofSoundPlayer* initSound;
public:
	std::vector<particleForce*> forces;
	particleSystem();
	void initSoundPlay(ofSoundPlayer* _initSound);
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

class impulseForce : public particleForce
{
private:
	float strength;
public:
	impulseForce(float);
	void updateParticle(particle* particle) const;
	bool applyOnce() const;
};

class turbulanceForce : public particleForce
{
private:
	glm::vec2 min, max;
public:
	turbulanceForce(const glm::vec2&, const glm::vec2&);
	void updateParticle(particle* particle) const;
	bool applyOnce() const;
};

class screenDragForce : public particleForce
{
private:
	float speed;
public:
	screenDragForce(float);
	void updateParticle(particle* particle) const;
	bool applyOnce() const;
	void setSpeed(float spd) { speed = spd; }
};

class trailForce : public particleForce
{
public:
	float mag_max, mag_min;
	float radius;
	glm::vec2 origin;
	glm::vec2 dir;
	trailForce(const glm::vec2& o, const glm::vec2& d, float r, float magm, float magM);
	void updateParticle(particle* particle) const;
	bool applyOnce() const;
};

class washForce : public particleForce
{
public:
	glm::vec2 origin;
	float mag_max, mag_min;
	washForce(const glm::vec2& o, float magm, float magM);
	void updateParticle(particle* particle) const;
	bool applyOnce() const;
};