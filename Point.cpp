#include "Point.hpp"

/***************************************************************************/
namespace Point
{ 

Point::Point( int _x, int _y ):
		m_x( _x )
	,	m_y( _y )
	,	m_status( PointStatus::Empty )
{}

/***************************************************************************/

Point::Point():
		m_x(0)
	,	m_y(0)
	,	m_status ( PointStatus::Empty )
{}

/***************************************************************************/

bool 
Point::operator==( const Point & _point ) const 
{
	return m_x == _point.m_x && m_y == _point.m_y;
}


/***************************************************************************/

} // namespace Point
