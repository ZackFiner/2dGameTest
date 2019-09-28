#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(ofColor::black);
	helicopter = new heliSprite(&sceneGraph, &collisionEngine);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	sceneGraph.update();
	collisionEngine.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	ofPushMatrix();
	ofTranslate(glm::vec3(ofGetWidth()/2, ofGetHeight()/2, 0));
	ofRotateDeg(180.0f);
	//collisionEngine.drawDebug();
	sceneGraph.draw();

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	helicopter->handleKeyInput(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	helicopter->handleKeyRelease(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

ofApp::~ofApp()
{
	/*
	delete box;
	for (auto sbox : sceneObjects)
	{
		delete sbox;
	}*/
	sceneGraph.clear();
}