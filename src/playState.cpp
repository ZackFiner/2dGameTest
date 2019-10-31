#include "playState.h"

/*H******************************************************************
 * FILENAME: gameState.h
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
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
	sceneGraph.setPlayer(helicopter->getID());
	spawner = new tankSpawner(&sceneGraph, &collisionEngine);
	startTick = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void playState::update() {
	//helicopter->setGunAng(cannonDir);
	//helicopter->setGunRPM(rpm);
	background.update();
	sceneGraph.update();
	collisionEngine.update();
	if (sceneGraph.getSprite(sceneGraph.getPlayer()) != nullptr)
	{
		heliSprite* p = (heliSprite*)sceneGraph.getSprite(sceneGraph.getPlayer());
		playerScore = p->getScore();
		hud.score = playerScore;
		hud.health = p->getHealth();
		spawner->setDifficulty(playerScore / 100);
	}
	else
	{
		
		if (deathTick == 0) // if we just died
		{
			deathTick = ofGetSystemTimeMillis();//set the death tick
			spawner->stop();
			hud.health = 0;
		}
		spooldown = (float)(ofGetSystemTimeMillis() - deathTick)/(GAME_END_PHASE*0.5f);
		background.setSpeed(300.0f*glm::max(1 - spooldown, 0.0f));

	}
	if (!spawner->getRunning() && ofGetSystemTimeMillis() - startTick > GAME_START_PHASE && deathTick==0)
	{
		spawner->start();
	}
}

//--------------------------------------------------------------
void playState::draw() {

	background.draw();
	glm::vec2 scrnDim = glm::vec2(ofGetWidth(), ofGetHeight());
	ofPushMatrix();
	ofTranslate(glm::vec3(ofGetWidth() / 2, ofGetHeight() / 2, 0));
	ofRotateDeg(180.0f);
	if (spooldown != -1.0f)
		ofTranslate(glm::vec2(0, 300 * spooldown));
	//collisionEngine.drawDebug();
	sceneGraph.draw();

	ofPopMatrix();
	std::stringstream ss;
	if (sceneGraph.getSprite(sceneGraph.getPlayer()) != nullptr)
	{
		heliSprite* p = (heliSprite*)sceneGraph.getSprite(sceneGraph.getPlayer());
		ss << "Score: " << p->getScore() << "\n";
		ss << "Health: " << p->getHealth() << "\n";
	}
	else
	{
		ss << "YOU DIED\n";
	}
	ofDrawBitmapString(ss.str(), glm::vec2(0,ofGetHeight()-20));

	/*
		Below is a little fade in effect.
	*/
	if (!spawner->getRunning()) //warm up phase basically
	{
		float ready = glm::min((float)(ofGetSystemTimeMillis() - startTick) / (GAME_START_PHASE*0.5f), 1.0f);
		ofSetColor(0, 0, 0, (1.0f - ready) * 255);
		ofDrawRectangle(glm::vec2(0, 0), ofGetWidth(), ofGetHeight());
		ofSetColor(ofColor::white);
	}
	hud.draw();
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