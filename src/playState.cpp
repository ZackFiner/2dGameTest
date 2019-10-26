#include "playState.h"

/*H******************************************************************
 * FILENAME: gameState.h
 * AUTHOR: Zackary Finer
 *
 * DESCRIPTION:
 * playState is the state associated with gameplay (when the player
 * is flying the helicopter and shooting things). As such, it contains
 * a helicopter sprite and various other critical data structures (
 * such as a scene manager and collision engine).
 *
 ********************************************************************/

void playState::setup() {
	ofSetBackgroundColor(ofColor::white);
	helicopter = new heliSprite(&sceneGraph, &collisionEngine);
	helicopter->setUpdateCannonDir(true);
	spawner = new tankSpawner(&sceneGraph, &collisionEngine);
	debugGui.setup();
	debugGui.add(rpm.setup("gun RPM", 600, 60, 2000));//starts at a M2, max is a GAU-12
	debugGui.add(cannonDir.setup("gun Direction (in degrees)", 0, -180, 180));

}

//--------------------------------------------------------------
void playState::update() {
	//helicopter->setGunAng(cannonDir);
	//helicopter->setGunRPM(rpm);
	background.update();
	sceneGraph.update();
	collisionEngine.update();
}

//--------------------------------------------------------------
void playState::draw() {
	background.draw();
	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	ofPushMatrix();
	ofTranslate(glm::vec3(ofGetWidth() / 2, ofGetHeight() / 2, 0));
	ofRotateDeg(180.0f);
	//collisionEngine.drawDebug();
	sceneGraph.draw();

	ofPopMatrix();
	debugGui.draw();
	std::stringstream ss;
	//ss << "Score: " << helicopter->getScore() << "\n";
	//ss << "Health: " << helicopter->getHealth() << "\n";
	ofDrawBitmapString(ss.str(), glm::vec2(0,ofGetHeight()-20));
}

//--------------------------------------------------------------
void playState::keyPressed(int key) {
	sceneGraph.handleKeyPressed(key);
}

//--------------------------------------------------------------
void playState::keyReleased(int key) {
	sceneGraph.handleKeyRelease(key);
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