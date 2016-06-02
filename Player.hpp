#ifndef __Player_HPP__
#define __Player_HPP__

/***************************************************************************/

#include "Point.hpp"
#include <unordered_map>
#include <unordered_set>

/***************************************************************************/

class Player
{

	typedef std::unordered_set< Point::Point, Point::Hasher > connections;

	typedef std::pair< Point::Point, connections > pointConnections;

/***************************************************************************/

public:

/***************************************************************************/

	Player( const std::string _name );

	Player(const Player &) = delete;

	Player & operator = (const Player &) = delete;

	bool isTriangle() const;

	void addPoints( const Point::Point & _point, const Point::Point _second );

	const std::string & getName() const;

	bool hasPoint( const Point::Point & _point ) const; 

	bool areConnected( const Point::Point & _first, const Point::Point & _second ) const;

/***************************************************************************/

	bool processPoint(const pointConnections & _point) const;

/***************************************************************************/

private:

/***************************************************************************/

	const std::string m_name;

	std::unordered_map< Point::Point, connections, Point::Hasher > m_points;

/***************************************************************************/

};

/***************************************************************************/

inline const std::string & 
Player::getName() const
{
	return m_name;
}

inline bool 
Player::hasPoint(const Point::Point & _point) const
{
	return m_points.find(_point) != m_points.end();
}


/***************************************************************************/

#endif // !__Player_HPP__
