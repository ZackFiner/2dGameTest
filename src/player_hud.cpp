#include "player_hud.h"
/*H****************************************************************************
 * 
 * FILENAME: player_hud.cpp
 * AUTHOR: Zackary Finer
 * DATE: 10/29/19
 *
 * DESCRIPTION:
 * PlayerHUD (heads up display) is a class used to manage all in game on screen
 * notifications. Aside from displaying basic ingame information (such as the
 * player's current health, score, and level) the HUD also shows on screen
 * pop ups such +20pts when an enemey is killed.
 * 
 * The following file contains implementations of methods associated with the
 * player hud class.
 *
 ******************************************************************************/
void playerHud::draw() const {

	for (auto notif : notifications)
		notif->draw();

	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	ofSetColor(ofColor::lightGray);
	ofDrawRectangle(glm::vec2(0, 0), scrnDim.x, 50);
	std::stringstream ss;
	
	ofSetColor(ofColor::red);
	ss << "HP " << health << "%";
	
	ofPushMatrix();
	
	ofScale(glm::vec3(1.0f));
	ofDrawBitmapString(ss.str(), glm::vec2(20.0f));
	
	ss.str(std::string());
	ss << "Score " << score << " pts";
	ofDrawBitmapString(ss.str(), glm::vec2(100.0f, 20.0f));

	ss.str(std::string());
	ss << "Level  " << level;
	ofDrawBitmapString(ss.str(), glm::vec2(250.0f, 20.0f));

	ofPopMatrix();
	ofSetColor(ofColor::white);
}

void playerHud::update()
{
	auto iter = notifications.begin();

	while (iter != notifications.end())
	{
		if (((*iter)->getLifeTime() >= 0.0f && (*iter)->getAge() > (*iter)->getLifeTime() ) ||
			 (*iter)->isDead())
		{
			delete (*iter);
			iter = notifications.erase(iter);
			continue;
		}
		iter++;
	}
	for (auto notif : notifications)
		notif->update();
}

void playerHud::addNotification(onScreenNotification * n)
{
	notifications.push_back(n);
}

playerHud::~playerHud()
{
	for (auto notif : notifications)
	{
		delete notif;
	}
}

onScreenNotification::onScreenNotification()
{}

onScreenNotification::onScreenNotification(const std::string& _text, float _lifetime)
{
	text = _text;
	lifetime = _lifetime;
}

void onScreenNotification::update()
{
	age += ofGetLastFrameTime();
}

float onScreenNotification::getLifeTime() const { return lifetime; }
float onScreenNotification::getAge() const { return age; }
glm::vec2 onScreenNotification::getPos() const { return pos; }
glm::vec2 onScreenNotification::getDim() const { return dim; }
float onScreenNotification::getRot() const { return rot; }
ofColor onScreenNotification::getColor() const { return col; }
bool onScreenNotification::isDead() const { return false; }
std::string onScreenNotification::getText() const { return text; }

void onScreenNotification::setPos(const glm::vec2& _p) { pos = _p; }
void onScreenNotification::setDim(const glm::vec2& _d) { dim = _d; }
void onScreenNotification::setRot(float _r) { rot = _r; }
void onScreenNotification::setColor(const ofColor& _col) { col = _col; }


popupNotification::popupNotification(const std::string& _text, float _lifetime, const glm::vec2& _pos, float _scale)
{
	//TODO:implement me
}

void popupNotification::update() {}

void popupNotification::draw() const {}
