#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Point.hpp"
#include "Player.hpp"
#include <vector>
#include <string>
#include <memory>

/***************************************************************************/

class Player;

class Game
{

/***************************************************************************/

	typedef std::vector< Point::Point >::const_iterator Iterator;

/***************************************************************************/

public:

/***************************************************************************/

	Game( const std::string & _first, const std::string & _second );

	Game(const Game &) = delete;

	Game & operator = (const Game &) = delete;

	Iterator beginPoints() const;
 
	Iterator endPoints() const;

/***************************************************************************/

private:

/***************************************************************************/

	std::vector < Point::Point > m_points;

	std::unique_ptr < Player > m_first;

	std::unique_ptr < Player > m_second;

/***************************************************************************/

}; // class Game

/***************************************************************************/

Game::Iterator
Game::beginPoints() const
{
	return m_points.begin();
}

/***************************************************************************/

Game::Iterator
Game::endPoints() const
{
	return m_points.end();
}

/***************************************************************************/

#endif // !__GAME_HPP__
