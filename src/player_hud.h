#pragma once
#include "ofMain.h"
/*H****************************************************************************
 *
 * FILENAME: player_hud.h
 * AUTHOR: Zackary Finer
 * DATE: 10/29/19
 *
 * DESCRIPTION:
 * PlayerHUD (heads up display) is a class used to manage all in game on screen
 * notifications. Aside from displaying basic ingame information (such as the
 * player's current health, score, and level) the HUD also shows on screen
 * pop ups such +20pts when an enemey is killed.
 *
 * The following file contains defintions of methods associated with the
 * player hud class.
 *
 ******************************************************************************/
class onScreenNotification;
class playerHud {
	std::vector<onScreenNotification*> notifications;
public:
	int score;
	int health;
	int level;
	void draw() const;
	void update();
	void addNotification(onScreenNotification* n);
	~playerHud();
};

class  onScreenNotification {
protected:
	float lifetime = -1.0f;
	float age = 0.0f;
	glm::vec2 pos, dim;
	float rot;
	ofColor col;
	std::string text;
public:
	onScreenNotification();
	onScreenNotification(const std::string& _text, float _lifetime);
	virtual void draw() const = 0;
	virtual void update();

	float getLifeTime() const;
	float getAge() const;
	virtual glm::vec2 getPos() const;
	virtual glm::vec2 getDim() const;
	virtual float getRot() const;
	virtual ofColor getColor() const;
	virtual bool isDead() const;
	
	virtual void setPos(const glm::vec2& _p);
	virtual void setDim(const glm::vec2& _d);
	virtual void setRot(float _r);
	virtual void setColor(const ofColor& _col);
	virtual std::string getText() const;
};

class popupNotification : public onScreenNotification
{
protected:
	float speed;
public:
	popupNotification(const std::string& _text, float _lifetime, const glm::vec2& _pos, float _speed);
	void update();
	void draw() const;
};