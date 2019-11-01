#include "menuState.h"
#include "ofMain.h"
#include "playState.h"

/*H******************************************************************
 * FILENAME: gameState.cpp
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * menuState represents the state in which the player is in the main
 * or start menu. Right now, it only prompts the player to press
 * space before transitioning into playState.
 *
 ********************************************************************/

void menuState::setup()
{
	background.resize(1024,1024);
	prop = new introHeliSprite(&em);
	prop->setPos(glm::vec2(5.0f, 10.0f));
}
void menuState::update()
{
	em.update();

	if (prop->getSpool() == 1.0f)
	{
		liftoff += 0.3 * ofGetLastFrameTime();
		liftoff = glm::clamp(liftoff, 0.0f, 1.0f);
		prop->scale = 0.5f + liftoff*0.5f;
		if (liftoff >= 0.3f)
		{
			flyoff += 0.3 * ofGetLastFrameTime();
			flyoff = glm::clamp(flyoff, 0.0f, 1.0f);
			prop->setPos(prop->getPos() + glm::vec2(0, flyoff*5.0f));
		}

		if (prop->getPos().y > 70.0f)
		{
			m_fadeout += ofGetLastFrameTime()*0.5f;
			m_fadeout = glm::clamp(m_fadeout, 0.0f, 1.1f);
		}
	}

	if (m_fadeout >= 1.0f && nextState == nullptr)
	{
		nextState = new playState();
	}

}
void menuState::draw()
{

	glm::vec2 dim = glm::vec2(ofGetWidth(), ofGetHeight());
	ofPushMatrix();
	ofTranslate(glm::vec3(ofGetWidth() / 2, ofGetHeight() / 2, 0));
	ofSetColor(ofColor::white);
	background.draw(glm::vec2(background.getWidth(), background.getHeight())*-0.5f);
	
	ofRotateDeg(180.0f);
	em.draw();
	ofPopMatrix();

	if (prop->getSpool() == 0.0f)
		ofDrawBitmapString("PRESS SPACE TO START GAME", dim / 2-glm::vec2(12.5*8,4));
	
	if (m_fadeout > 0.0f)
	{
		ofSetColor(0, 0, 0, (m_fadeout) * 255);
		ofDrawRectangle(glm::vec2(0, 0), ofGetWidth(), ofGetHeight());
	}
}
void menuState::keyPressed(int key)
{
	switch (key)
	{
	case ' ':
		prop->startUp();
	}
}
void menuState::keyReleased(int key)
{

}
void menuState::mouseMoved(int x, int y)
{

}
void menuState::mouseDragged(int x, int y, int button)
{

}
void menuState::mousePressed(int x, int y, int button)
{

}
void menuState::mouseReleased(int x, int y, int button)
{

}
void menuState::mouseEntered(int x, int y)
{

}
void menuState::mouseExited(int x, int y)
{

}
void menuState::windowResized(int w, int h)
{

}
void menuState::dragEvent(ofDragInfo dragInfo)
{

}
void menuState::gotMessage(ofMessage msg)
{

}
gameState* menuState::transitionState()
{
	return nextState;
}
menuState::~menuState()
{

}