#include "Field.hpp"
#include <ctime>
#include <cmath>
#include <cassert>
#include <iostream>

/***************************************************************************/

Field::Field()
{
	time_t current; // рандомизируем. 
	time(&current);
	srand((unsigned int)current);

	m_count = rand() % 15 + 6;

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

		if (dis < 25.0)
			addPoint();
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

