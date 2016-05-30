#ifndef __Player_HPP__
#define __Player_HPP__

/***************************************************************************/

#include "Point.hpp"
#include <unordered_set>
#include <vector>

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

/***************************************************************************/

private:

/***************************************************************************/

	const std::string m_name;

	std::vector< Point::Point > m_points;

/***************************************************************************/

};

/***************************************************************************/

inline const std::string & 
Player::getName() const
{
	return m_name;
}


/***************************************************************************/

#endif // !__Player_HPP__
