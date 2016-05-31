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
	if (m_points.size() < 3)
		return false;

	for (auto const & point : m_points)
		if ( processPoint(point) )
			return true;

	return false;
}


/***************************************************************************/

bool 
Player::processPoint(const Point::Point & _point) const
{
	for ( auto f_connections : _point.getConnections() )
		for (auto s_connection : f_connections->getConnections())
			if ( _point.hasConnection(*  s_connection) || s_connection->hasConnection( _point) )
				return true;

	return false;
}

/***************************************************************************/

void 
Player::addPoint( const Point::Point & _point )
{
	m_points.push_back( _point );
}


/***************************************************************************/



