#pragma once
#include "ofMain.h"
class drawnObject {
public:
	virtual void setPos(const glm::vec2&) = 0;
	virtual bool inBoundry(const glm::vec2&) = 0;
	virtual void draw() = 0;
	ofColor color = ofColor::red;
};

class dTriangle : public drawnObject
{
private:
	glm::vec2 pt0, pt1, pt2;
public:
	dTriangle(const glm::vec2&, const glm::vec2&, const glm::vec2&);
	void setPos(const glm::vec2&);
	bool inBoundry(const glm::vec2&);
	void draw();
};

class dSquare : public drawnObject
{
private:
	glm::vec2 pos;
	float size;
public:
	dSquare(const glm::vec2&, float);
	void setPos(const glm::vec2&);
	bool inBoundry(const glm::vec2&);
	void draw();
};