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

	void addPoint(const Point::Point & _point);

	Field & getField() const;

	std::string getWinner() const;

/***************************************************************************/

private:

/***************************************************************************/

	std::unique_ptr < Player > m_first;

	std::unique_ptr < Player > m_second;

	std::unique_ptr< Field > m_field;

	bool m_step;

/***************************************************************************/

}; // class Game

/***************************************************************************/

inline Field &
Game::getField() const
{
	return * m_field;
}

/***************************************************************************/

#endif // !__GAME_HPP__
