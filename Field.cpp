#include "Field.hpp"
#include <ctime>
#include <cmath>
#include <cassert>
#include <iostream>
#include "globals.hpp"

/***************************************************************************/

Field::Field()
	: m_count ( rand() % 15 + 6 )
{
	time_t current; // рандомизируем. 
	time(&current);
	srand((unsigned int)current);

	for (int i = 0; i < m_count; i++)
		addPoint();
}


/***************************************************************************/


void
Field::addPoint() 
{
	int x = rand() % 400;

	int y = rand() % 400;

	Point::Point newPoint(x, y);

	for (auto point : m_points)
	{
		double dis = distance(point, newPoint);

	}
	m_points.push_back(newPoint);
}

double
Field::distance( const Point::Point & _first, const Point::Point _second ) const
{
	int xDistance = _first.getX() - _second.getX();
	int yDistance = _first.getY() - _second.getY();

	return sqrt(xDistance * xDistance + yDistance * yDistance);
}

/***************************************************************************/

const Point::Point *
Field::onClicked( int _x, int _y )
{
	Point::Point * clicked = nullptr;

	for (auto & point : m_points)
	{
		int x = point.getX();
		int y = point.getY();

		if (_x >= x && _x <= x + Globals::diameter && _y >= y && _y <= y + Globals::diameter )
			clicked = & point;
	}

	clicked->setStatus(Point::PointStatus::Filled);

	return clicked;
}

/***************************************************************************/

