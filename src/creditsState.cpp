#include "creditsState.h"
#include "menuState.h"
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
void creditsState::setup() {
	ofSetBackgroundColor(ofColor::black);
}

//--------------------------------------------------------------
void creditsState::update() {

}

//--------------------------------------------------------------
void creditsState::draw() {
	glm::vec2 dim = glm::vec2(ofGetWidth(), ofGetHeight());
	std::stringstream ss;
	ss << "Developer: " << "Zackary Finer\n";
	ss << "Sprite Art: " << "Zackary Finer\n";
	ss << "Music and Audio:\n" << "Sunrise Over Los Angelos - TeknoAXE\n" << "SFX - Sourced from FreeSound.org";
	ofDrawBitmapString(ss.str(), dim / 2 - glm::vec2(19.5 * 8, 2.5*8));
	ofDrawBitmapString("PRESS SPACE TO RETURN TO MENU", dim / 2 - glm::vec2(12.5 * 8, -200));
}

//--------------------------------------------------------------
void creditsState::keyPressed(int key) {
	switch (key)
	{
	case ' ':
		nextState = (gameState*) new menuState();
	}
}

//--------------------------------------------------------------
void creditsState::keyReleased(int key) {
}

//--------------------------------------------------------------
void creditsState::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void creditsState::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void creditsState::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void creditsState::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void creditsState::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void creditsState::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void creditsState::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void creditsState::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void creditsState::dragEvent(ofDragInfo dragInfo) {

}

gameState* creditsState::transitionState()
{
	return nextState;
}
