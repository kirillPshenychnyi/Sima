#include "Point.hpp"

/***************************************************************************/
namespace Point
{ 

Point::Point( int _x, int _y ):
		m_x( _x )
	,	m_y( _y )
	,	m_status( PointStatus::Empty )
	,	m_connected(nullptr)
{}

/***************************************************************************/

void 
Point::connect(Point * _destination)
{
	m_connected = _destination;
}

const Point * 
Point::getDestination() const
{
	return m_connected;
}

/***************************************************************************/

bool 
Point::operator==( const Point & _point ) const 
{
	return m_x == _point.m_x && m_y == _point.m_y;
}

bool 
Point::operator!=(const Point & _point) const
{
	return !( *this == _point );
}


/***************************************************************************/

} // namespace Point
