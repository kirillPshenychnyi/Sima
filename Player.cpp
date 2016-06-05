#include "Player.hpp"

/***************************************************************************/

Player::Player(const std::string _name)
	:	m_name( _name ) 
{
}

/***************************************************************************/


bool 
Player::isTriangle()
{
	if (m_points.size() < 2)
		return false;

	for (auto const & point : m_points)
		if (processPoint(point))
			return true;

	return false;
}


/***************************************************************************/

bool 
Player::processPoint(const pointConnections & _point)
{
	for ( auto & f_connections : _point.second )
		for (auto & s_connection : m_points.find( f_connections )->second )
			if (areConnected(s_connection, _point.first) || areConnected(_point.first, s_connection))
			{
				m_triangle.push_back(_point.first);
				m_triangle.push_back(f_connections);
				m_triangle.push_back(s_connection);
				return true;
			}

	return false;
}


/***************************************************************************/

void 
Player::addPoints( const Point::Point & _first, const Point::Point _second )
{
	if (!hasPoint(_first))
		m_points.insert( std::make_pair ( _first, connections() ) );

	m_points[_first].insert(_second);

	m_points.insert(std::make_pair(_second, connections()));

}

/***************************************************************************/

bool 
Player::areConnected (const Point::Point & _first, const Point::Point & _second ) const 
{
	const auto & connections = m_points.find(_first);

	return connections->second.find( _second) != connections->second.end();
}

/***************************************************************************/



/***************************************************************************/
