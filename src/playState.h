#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "gameState.h"
#include "drawnObject.h"
#include "entityManager.h"
#include "collisionManager.h"
#include "boxSprite.h"
#include "heliSprite.h"
#include "scrollingBg.h"
#include "tankSpawner.h"
#include "GameSettings.h"
#include "player_hud.h"

/*H******************************************************************
 * FILENAME: gameState.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * playState is the state associated with gameplay (when the player
 * is flying the helicopter and shooting things). As such, it contains
 * a helicopter sprite and various other critical data structures (
 * such as a scene manager and collision engine).
 *
 ********************************************************************/


class playState : public gameState
{
	entityManager sceneGraph;
	simpleCollisionManager collisionEngine;
	drawnObject* dragTarget;
	heliSprite* helicopter;
	tankSpawner* spawner;
	scrollingBg background = scrollingBg("background.png", 300.0f);
	ofxFloatSlider rpm;
	ofxFloatSlider cannonDir;
	ofxPanel debugGui;
	unsigned long startTick;
	playerHud hud;
public:
	int playerScore;
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
	~playState();
};