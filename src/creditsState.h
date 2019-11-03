#pragma once
#include "gameState.h"
/*H**********************************************************
 *
 * FILENAME: creditsState.h
 * AUTHOR: Zackary Finer
 * DATE: 10/31/2019
 *
 * DESCRIPTION:
 * Credits state is just a screen that displays credits for the
 * game. This is necessary because some of the resources used
 * are licensed under creative commons 4.0, which mandates 
 * that attribution is given to the artists of the resources.
 *
 ************************************************************/


class creditsState : gameState
{
	gameState* nextState = nullptr;
public:
	virtual void setup();
	virtual void update();
	virtual void draw();

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mouseDragged(int x, int y, int button);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);
	virtual void mouseEntered(int x, int y);
	virtual void mouseExited(int x, int y);
	virtual void windowResized(int w, int h);
	virtual void dragEvent(ofDragInfo dragInfo);
	virtual void gotMessage(ofMessage msg);
	virtual gameState* transitionState();
};