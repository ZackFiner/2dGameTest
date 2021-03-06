#include "spriteSheet.h"

/*H******************************************************************
 * FILENAME: spriteSheet.cpp
 * AUTHOR: Zackary Finer
 * DATE: 10/26/2019
 *
 * DESCRIPTION:
 * spriteSheet is a class which can be used to draw animated sprites
 * using a spriteSheet. It is currently used by the helicopter class
 * to draw the spinning rotor blades.
 *
 ********************************************************************/

spriteSheet::spriteSheet(const std::string& fpath, float frequency, const glm::vec2& desiredSize, const glm::vec2& frameSize, int frameCount):
	sheet(fpath)
{
	this->frequency = frequency;
	dim = desiredSize;
	this->frameCount = frameCount;
	sheet.mirror(true, false);
	float nX = desiredSize.x / frameSize.x;
	float nY = desiredSize.y / frameSize.y;
	adj = glm::vec2(nX, nY);
	sheet.resize(sheet.getWidth()*adj.x, sheet.getHeight()*adj.y);
}

void spriteSheet::update()
{
	unsigned long updateT = ofGetCurrentTime().getAsMilliseconds();
	if (updateT - lstF > frequency)
	{
		curFrame++;
		curFrame = curFrame % frameCount;
		lstF = updateT;
	}
}

glm::vec2 spriteSheet::getSize()
{
	return dim;
}

void spriteSheet::draw(const glm::vec2& pos) const
{
	int numRow = sheet.getWidth() / dim.x;
	int numCol = sheet.getHeight() / dim.y;
	glm::vec2 framePos = glm::vec2(
		(curFrame % numRow)*dim.x,
		(curFrame*numRow % numCol)*dim.y
	);
	sheet.drawSubsection(pos.x, pos.y, dim.x, dim.y, framePos.x, framePos.y);
}