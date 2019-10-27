#include "player_hud.h"

void playerHud::draw() const {
	
	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	ofSetColor(ofColor::lightGray);
	ofDrawRectangle(glm::vec2(0, scrnDim.y-50), scrnDim.x, 50);
}