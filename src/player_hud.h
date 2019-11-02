#pragma once
#include "ofMain.h"

class playerHud {

public:
	int score;
	int health;
	int level;
	void draw() const;
	void queueNotification(std::string notif);
};