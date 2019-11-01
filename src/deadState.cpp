#include "deadState.h"
#include "playState.h"
/*H**********************************************************
 *
 * FILENAME: deadState.h
 * AUTHOR: Zackary Finer
 * DATE: 10/31/2019
 *
 * DESCRIPTION:
 * Dead state is a relatively simple game state: it displays
 * the score from the last played game, and prompts the user
 * to restart.
 *
 ************************************************************/
void deadState::setup() {
	ofSetBackgroundColor(ofColor::black);
}

//--------------------------------------------------------------
void deadState::update() {

}

//--------------------------------------------------------------
void deadState::draw() {
	glm::vec2 dim = glm::vec2(ofGetWidth(), ofGetHeight());
	std::stringstream ss;
	ss << "YOU SCORED: " << score << std::endl;
	ofDrawBitmapString(ss.str() , dim / 2 - glm::vec2(12.5 * 8, 12));
	ofDrawBitmapString("PRESS SPACE TO REPLAY GAME", dim / 2 - glm::vec2(12.5 * 8, -8));
}

//--------------------------------------------------------------
void deadState::keyPressed(int key) {
	switch (key)
	{
	case ' ':
		nextState = (gameState*) new playState();
	}
}

//--------------------------------------------------------------
void deadState::keyReleased(int key) {
}

//--------------------------------------------------------------
void deadState::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void deadState::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void deadState::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void deadState::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void deadState::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void deadState::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void deadState::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void deadState::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void deadState::dragEvent(ofDragInfo dragInfo) {

}

gameState* deadState::transitionState()
{
	return nextState;
}

deadState::~deadState()
{
}