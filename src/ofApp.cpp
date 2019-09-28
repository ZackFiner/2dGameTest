#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	currentState = new menuState();
	currentState->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	currentState->update();
	gameState* nextState;
	if ((nextState = currentState->transitionState())!=nullptr) //handle state transition
	{
		delete currentState; // de-allocate old state
		currentState = nextState;
		currentState->setup();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	currentState->draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	currentState->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	currentState->dragEvent(dragInfo);
}

ofApp::~ofApp()
{
	delete currentState;
}