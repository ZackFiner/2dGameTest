#include "playState.h"

void playState::setup() {
	ofSetBackgroundColor(ofColor::white);
	helicopter = new heliSprite(&sceneGraph, &collisionEngine);

}

//--------------------------------------------------------------
void playState::update() {
	sceneGraph.update();
	collisionEngine.update();
}

//--------------------------------------------------------------
void playState::draw() {

	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	ofPushMatrix();
	ofTranslate(glm::vec3(ofGetWidth() / 2, ofGetHeight() / 2, 0));
	ofRotateDeg(180.0f);
	//collisionEngine.drawDebug();
	sceneGraph.draw();

	ofPopMatrix();
}

//--------------------------------------------------------------
void playState::keyPressed(int key) {
	helicopter->handleKeyInput(key);
}

//--------------------------------------------------------------
void playState::keyReleased(int key) {
	helicopter->handleKeyRelease(key);
}

//--------------------------------------------------------------
void playState::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void playState::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void playState::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void playState::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void playState::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void playState::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void playState::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void playState::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void playState::dragEvent(ofDragInfo dragInfo) {

}

gameState* playState::transitionState()
{
	return nullptr;
}

playState::~playState()
{
	/*
	delete box;
	for (auto sbox : sceneObjects)
	{
		delete sbox;
	}*/
	sceneGraph.clear();
}