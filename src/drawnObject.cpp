#include "drawnObject.h"

dTriangle::dTriangle(const glm::vec2& _p0, const glm::vec2& _p1, const glm::vec2& _p2) :
	pt0(_p0),
	pt1(_p1),
	pt2(_p2)
{}

void dTriangle::setPos(const glm::vec2& _pos)
{
	glm::vec2 diff = _pos - ((pt0 + pt1 + pt2) / 3);
	pt0 += diff;
	pt1 += diff;
	pt2 += diff;
}

bool dTriangle::inBoundry(const glm::vec2& _p)
{
	//This method uses the barycentric technique.
	//CITATION - As described on: http://blackpawn.com/texts/pointinpoly/default.html

	/*
	Basically, barrycentric coords modify a coordinate system in such a way that the axis vectors
	allign with the corners of a triangle, or more generally simplex (which will come in handy for
	collision detection later on). (*) As such, if you were to shade the region of this coordinate system
	between the x and y axis, and the line y = 1 - x, the region would look exactly like a triangle which has
	the two edge vectors used as axis.

	The matrix used to transform barycentric coordinates into cartesian coordinates is pretty simple:
	M = [v1, v2], where v1 and v2 are the edge vectors of the triangle. that is, you simply use these vectors
	as the column vectors of a matrix.

	As such, if we wanted to transform a cartesian coordinate into a barycentric coordinate (perhaps to more
	easily test whether a point falls within a specific triangular region), we could calculate this
	inverse matrix and multiply the cartesian point by it to get it's barycentric equivalent.

	Once this is done, testing to see whether the point falls within the triangle is as trivial as testing to
	see whether it is in the region x,y>0 x+y<1 (*).

	This, in principle, is what the code below does.
	*/


	glm::vec2 e1 = pt1 - pt0;
	glm::vec2 e2 = pt2 - pt0;
	/*
	Note below that we calculate pt, by adjusting the actual point to be relative to the
	position of the vertex our edge vectors originate from. This is important, as our test will
	assume that the point we are testing exists in a coordinate system where v1 is the origin.
	*/
	glm::vec2 pt = _p - pt0 - _p;
	/*
	Next, we calculate the inverse matrix and apply it to the point we're testing.
	You may notice that in the website cited, this was done by manually calculating
	the 5 dot products. This is slightly more efficient, but i feel that
	using the inverse function in glm better illustrates the intuition behind this approach.
	*/
	glm::vec2 bCoords = glm::inverse(glm::mat2(e1, e2))*pt;
	/*
	Finally, now that we have our barycentric equivalent for the point, to test if it
	falls within the triangle, we simply need to test if it falls in the triangle formed
	by the intersection of the x = 0, y = 0, and y = 1-x (*)
	*/
	return (bCoords.x >= 0 && bCoords.y >= 0 && bCoords.x + bCoords.y <= 1);

}

void dTriangle::draw()
{
	ofDrawTriangle(pt0, pt1, pt2);
}

dSquare::dSquare(const glm::vec2& _pos, float _size):
	pos(_pos),
	size(_size)
{}

void dSquare::setPos(const glm::vec2& _pos)
{
	pos = _pos;
}

bool dSquare::inBoundry(const glm::vec2& _p)
{
	glm::vec2 min, max;
	min = pos;
	max = pos + (glm::vec2(size, size));
	return _p.x > min.x && _p.y > min.y && _p.x < max.x && _p.y < max.y;
}

void dSquare::draw()
{
	ofDrawRectangle(pos, size, size);
}
