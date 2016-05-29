#include "Field.hpp"
#include <ctime>

/***************************************************************************/

Field::Field()
{
	time_t current; // рандомизируем. 
	time(&current);
	srand((unsigned int)current);

}


/***************************************************************************/


void
Field::addPoint() 
{
	int x = rand() % 250;

	int y = rand() % 100;

	if (m_points.empty())
		m_points.insert( Point::Point(x, y) );
	else
	{
		auto lastPoint = m_points.end()--;
		
		int lastX = lastPoint->getX();

		int lastY = lastPoint->getY();

		x = lastX + (rand() % 50 - 100);

		y = lastX + (rand() % 50 - 100);

		Point::Point newPoint(x, y);

		if (m_points.find(newPoint) != m_points.end())
			addPoint();
	}
	
}



