#include "particle.h"
#include "particleSystem.h"
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
imageSingleton& getImageLib()
{
	static imageSingleton* lib = new imageSingleton();
	return *lib;
}
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
float particle::getMass()
{
	return mass;
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
		float alpha = (lifetime - age) / lifetime;
		ofSetColor(col.r, col.g, col.b, alpha*255);
		ofDrawRectangle(glm::vec2(), dim.x, dim.y);
		ofSetColor(ofColor::white);
	ofPopMatrix();
}

float particle::getAge() const { return age; }
float particle::getLifetime() const{ return lifetime; }

particle::~particle() {}


smokeParticle::smokeParticle(const glm::vec2& _pos, const glm::vec2& _vel, const glm::vec2& _acc, float _mass, float _lifetime) :
	particle(_pos,_vel,_acc,_mass,_lifetime)
{
	rot = ofRandom(360.0f);
	rot_dir = ofRandomf()*60.0f;
	this->dim = glm::vec2(60, 60);
}
smokeParticle::smokeParticle(const glm::vec2& _pos, float _lifetime) :
	particle(_pos, _lifetime)
{
	rot = ofRandom(360.0f);
	rot_dir = ofRandomf()*60.0f;
	this->dim = glm::vec2(60, 60);
}
void smokeParticle::setSizeGradient(float min, float max)
{
	min_size = min;
	max_size = max;
}
void smokeParticle::draw() const
{
	ofPushMatrix();
	
	float normal_l = age / lifetime;
	ofSetColor(colOverride.r, colOverride.g, colOverride.b,(1-normal_l)*255);
	
	float size = (max_size - min_size)*normal_l;
	ofTranslate(pos);
	ofScale(glm::vec3(min_size + size));
	ofRotate(rot);
	getImageLib().smoke.draw(dim*-0.5f);
	
	ofPopMatrix();

}
void smokeParticle::integrate()
{
	rot += rot_dir * ofGetLastFrameTime();
	particle::integrate();
}

smokeStreamer::smokeStreamer(const glm::vec2& _pos, 
	const glm::vec2& _vel,
	const glm::vec2& _acc,
	float _mass,
	float _lifetime,
	float trail_length,
	float trail_density,
	particleSystem* sys)
	:
	smokeParticle(_pos, _vel, _acc, _mass, _lifetime)
{
	this->trail_length = trail_length;
	this->trail_density = trail_density;
	this->sys = sys;
}

smokeStreamer::smokeStreamer(const glm::vec2& _pos,
	float _lifetime,
	float trail_length,
	float trail_density,
	particleSystem* sys)
	:
	smokeParticle(_pos, _lifetime)
{
	this->trail_length = trail_length;
	this->trail_density = trail_density;
	this->sys = sys;
}

void smokeStreamer::integrate()
{
	smokeParticle::integrate();
	unsigned long cT = ofGetSystemTimeMillis();
	if (trail_density > 0)
	{
		if (cT - lastSpawn > (1000.0f / trail_density))
		{
			smokeParticle* p = new smokeParticle(pos, glm::vec2(), glm::vec2(), mass, trail_length);
			p->colOverride = colOverride;
			p->setSizeGradient(0.3f, 1.0f);
			sys->spawnParticle((particle*)p);
			lastSpawn = cT;
		}
	}
}