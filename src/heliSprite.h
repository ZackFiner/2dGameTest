#pragma once
#include "solidEntity.h"
#include "emitter.h"
#include "projectileEmitter.h"
#include "spriteSheet.h"
class heliSprite : public solidEntity
{
	int health = 100;
	projectileEmitter* gun;
	glm::vec2 vel;
	float f=0.0f, l = 0.0f, r = 0.0f, b = 0.0f;
	float angAcc, angV;
	ofImage img;
	spriteSheet rotor;
	ofSoundPlayer main, whine;
	glm::vec2 dim;
public:
	heliSprite(entityManager*, collisionManager*);
	void draw();
	bool isDead() const;
	void update();
	int getHealth() const;
	void setHealth(int);
	void handleKeyInput(int);
	void handleKeyRelease(int);
	~heliSprite();
};