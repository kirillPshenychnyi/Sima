#include "Point.hpp"

/***************************************************************************/
namespace Point
{ 

Point::Point( int _x, int _y ):
		m_x( _x )
	,	m_y( _y )
{}


/***************************************************************************/

bool 
Point::operator==( const Point & _point ) const 
{
	return m_x == _point.m_x && m_y == _point.m_y;
}

/***************************************************************************/

} // namespace Point
