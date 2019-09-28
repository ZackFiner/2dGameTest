#pragma once

#include "ofMain.h"
#include "gameState.h"
#include "drawnObject.h"
#include "entityManager.h"
#include "collisionManager.h"
#include "boxSprite.h"
#include "heliSprite.h"
#include "scrollingBg.h"
class playState : public gameState
{
	entityManager sceneGraph;
	quadTreeCollisionManager collisionEngine;
	drawnObject* dragTarget;
	heliSprite* helicopter;
	scrollingBg background = scrollingBg("background.png", 3.0f);
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
	~playState();
};