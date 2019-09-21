#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	sceneObjects.push_back(new dTriangle(glm::vec2(100, 50), glm::vec2(150, 80), glm::vec2(70, 100)));
	sceneObjects.push_back(new dSquare(glm::vec2(200, 200), 50.0f));
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (drawnObject* obj : sceneObjects)
	{
		ofSetColor(obj->color);
		obj->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (dragTarget != nullptr)
		dragTarget->setPos(glm::vec2(x, y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for (drawnObject* obj : sceneObjects)
	{
		if (obj->inBoundry(glm::vec2(x, y)))
		{
			dragTarget = obj;
			obj->color = ofColor::green;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (dragTarget != nullptr)
		dragTarget->color = ofColor::red;
	dragTarget = nullptr;
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
	// de-allocate our vector
	for (drawnObject* v: sceneObjects)
		delete v;
}