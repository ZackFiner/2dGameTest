#pragma once
#include "gameState.h"
#include "particleEmitter.h"
#include "heliSprite.h"
#include "scrollingBg.h"

/*H******************************************************************
 * FILENAME: gameState.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * menuState represents the state in which the player is in the main
 * or start menu. Right now, it only prompts the player to press
 * space before transitioning into playState.
 *
 ********************************************************************/

class menuState : public gameState
{
	gameState* nextState = nullptr;
	entityManager em;
	introHeliSprite* prop;
	ofImage background = ofImage("background_m.png");
	float liftoff = 0.0f;
	float flyoff = 0.0f;
	float m_fadeout = 0.0f;
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	gameState* transitionState();
	~menuState();
};