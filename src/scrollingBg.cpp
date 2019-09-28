#include "scrollingBg.h"

scrollingBg::scrollingBg(const std::string& fpath, float spd) :
	tile1(fpath),
	tile2(fpath)
{
	float resize = ofGetWidth()/tile1.getWidth();
	glm::vec2 dim = glm::vec2(tile1.getWidth(), tile1.getHeight())*resize;
	//tile1.resize(dim.x, dim.y);
	//tile2.resize(dim.x, dim.y);
	speed = spd;
}

void scrollingBg::update()
{
	pos += glm::vec2(0.0f,1.0f)*speed;
}

void scrollingBg::draw() const
{
	
	tile1.draw(pos.x, (float)((int)(pos.y) % ((int)tile1.getHeight()*2)) - tile1.getHeight());
	tile2.draw(pos.x, (float)((int)(pos.y + tile2.getHeight()) % ((int)tile2.getHeight()*2))-tile2.getHeight());
}

void scrollingBg::setSpeed(float spd)
{
	speed = spd;
}