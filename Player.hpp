#ifndef __Player_HPP__
#define __Player_HPP__

/***************************************************************************/

#include "Point.hpp"
#include <unordered_set>
#include <string>

/***************************************************************************/

class Player
{

/***************************************************************************/

public:

/***************************************************************************/

	Player( const std::string _name );

	Player(const Player &) = delete;

	Player & operator = (const Player &) = delete;

	bool isTriangle() const;

	void addPoint( const Point::Point & _point );

	const std::string & getName() const;

	bool hasPoint(const Point::Point & _point) const;

/***************************************************************************/

private:

/***************************************************************************/

	const std::string m_name;

	std::unordered_set< Point::Point, Point::Hasher > m_points;

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
