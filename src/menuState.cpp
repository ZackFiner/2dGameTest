#include "menuState.h"
#include "ofMain.h"
#include "playState.h"
void menuState::setup()
{
	ofSetBackgroundColor(ofColor::black);
}
void menuState::update()
{

}
void menuState::draw()
{
	
	glm::vec2 dim = glm::vec2(ofGetWidth(), ofGetHeight());
	ofDrawBitmapString("PRESS SPACE TO START GAME", dim / 2 - (glm::vec2(8, 11 * 25) / 2));
}
void menuState::keyPressed(int key)
{
	switch (key)
	{
	case ' ':
		nextState = new playState();
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