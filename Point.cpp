#include "Point.hpp"
#include <algorithm>

/***************************************************************************/
namespace Point
{ 

Point::Point( int _x, int _y ):
		m_x( _x )
	,	m_y( _y )
	,	m_status( PointStatus::Empty )
{}

/***************************************************************************/

bool 
Point::operator==( const Point & _point ) const 
{
	return m_x == _point.m_x && m_y == _point.m_y;
}

/***************************************************************************/

void
Point::addConnection(const Point & _point)
{
	m_connections.push_back( & _point);
}

/***************************************************************************/

bool
Point::hasConnection(const Point & _point) const
{
	auto predicat = [&_point](const Point * _other)
	{
		return _point == *_other;
	};

	return std::find_if(m_connections.begin(), m_connections.end(), predicat) != m_connections.end();
}

/***************************************************************************/

} // namespace Point
