#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//sceneObjects.push_back(new dTriangle(glm::vec2(100, 50), glm::vec2(150, 80), glm::vec2(70, 100)));
	//sceneObjects.push_back(new dSquare(glm::vec2(200, 200), 50.0f));
	box = new boxSprite(&sceneGraph, 10.0f, &collisionEngine);
	collisionEngine.update();
	box->setPos(glm::vec2(20, 250));

	for (int i = 0; i < 500; i++)
	{
		boxSprite * sbox = new boxSprite(&sceneGraph, 10.0f, &collisionEngine);
		collisionEngine.update();
		sbox->setPos(glm::linearRand(glm::vec2(-500, -500), glm::vec2(500, 500)));
		sceneObjects.push_back(sbox);
	}
	
}

//--------------------------------------------------------------
void ofApp::update(){
	entity* asEnt = box;
	//std::cout << asEnt->getPos() << std::endl;
	for (auto box : sceneObjects)
	{
		box->setPos(box->getPos() + glm::diskRand(1.0f));
	}
	collisionEngine.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushMatrix();
	ofTranslate(glm::vec3(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 0));
	collisionEngine.drawDebug();
	sceneGraph.draw();
	ofPopMatrix();
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
	box->setPos(glm::vec2(x, y)-glm::vec2(ofGetWindowWidth(), ofGetWindowHeight())/2);
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
	delete box;
	for (auto sbox : sceneObjects)
	{
		delete sbox;
	}
}