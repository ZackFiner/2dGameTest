#include "player_hud.h"

void playerHud::draw() const {
	
	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	ofSetColor(ofColor::lightGray);
	ofDrawRectangle(glm::vec2(0, 0), scrnDim.x, 50);
	std::stringstream ss;
	
	ofSetColor(ofColor::red);
	ss << "HP " << health << "%";
	
	ofPushMatrix();
	ofScale(glm::vec3(2.0f));
	ofDrawBitmapString(ss.str(), glm::vec2(20.0f));
	ss.str(std::string());
	ss << "Score " << score << " pts";
	ofDrawBitmapString(ss.str(), glm::vec2(100.0f, 20.0f));
	ofPopMatrix();
	ofSetColor(ofColor::white);
}