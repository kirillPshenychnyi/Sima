#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Point.hpp"
#include "Player.hpp"
#include "Field.hpp"

#include <vector>
#include <string>
#include <memory>

/***************************************************************************/

class Player;

class Game
{

/***************************************************************************/

public:

/***************************************************************************/

	Game( const std::string & _first, const std::string & _second );

	Game(const Game &) = delete;

	Game & operator = (const Game &) = delete;

/***************************************************************************/

	const Field & getField() const;

/***************************************************************************/

private:

/***************************************************************************/

	std::vector < Point::Point > m_points;

	std::unique_ptr < Player > m_first;

	std::unique_ptr < Player > m_second;

	std::unique_ptr< Field > m_field;

/***************************************************************************/

}; // class Game

/***************************************************************************/

inline const Field & 
Game::getField() const
{
	return * m_field;
}

/***************************************************************************/

#endif // !__GAME_HPP__
