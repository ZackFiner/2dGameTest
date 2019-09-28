#pragma once
#include "ofMain.h"

/*H*************************************************************
 *
 * FILENAME: gameState.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION: 
 * It occured to me that to have a menu, I need some way
 * of seperating the logic for the game from the menu itself.
 *
 * For that reason, I've created a game state interface that
 * will allow me to have several different states without making
 * my code any messier than it already is.
 *
 * Looking at this, you may ask: "why not just use ofApp? This
 * looks just like ofApp". You're correct, I've set this up the
 * to look exactly like ofApp. However, my thinking was that the
 * classes that ofApp inherits from probably do a lot of stuff
 * (Initializes a window, binds opengl context to window, etc.)
 * that we don't want to re-do every time we transition state.
 *
 * Then again, I could be wrong in this assumption.
 *
 ***************************************************************/
class gameState
{
	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	virtual void keyPressed(int key) = 0;
	virtual void keyReleased(int key) = 0;
	virtual void mouseMoved(int x, int y) = 0;
	virtual void mouseDragged(int x, int y, int button) = 0;
	virtual void mousePressed(int x, int y, int button) = 0;
	virtual void mouseReleased(int x, int y, int button) = 0;
	virtual void mouseEntered(int x, int y) = 0;
	virtual void mouseExited(int x, int y) = 0;
	virtual void windowResized(int w, int h) = 0;
	virtual void dragEvent(ofDragInfo dragInfo) = 0;
	virtual void gotMessage(ofMessage msg) = 0;
	virtual gameState* tranitionState() = 0;
	virtual ~gameState() = 0;
};