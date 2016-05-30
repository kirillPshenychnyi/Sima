#include "Player.hpp"

/***************************************************************************/

Player::Player(const std::string _name)
	:	m_name( _name ) 
{
}

/***************************************************************************/


bool 
Player::isTriangle() const
{
	for (auto const & point : m_points)
		if (processPoint(point))
			return true;

	return false;
}


/***************************************************************************/

bool 
Player::processPoint(const Point::Point & _point) const
{
	return false;
}

/***************************************************************************/

void 
Player::addPoint( const Point::Point & _point )
{
	m_points.push_back( _point );
}


/***************************************************************************/



