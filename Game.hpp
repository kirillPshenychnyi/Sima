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

	void addPoints( const Point::Point & _first, const Point::Point & _second );

	Field & getField() const;

	std::string getWinner();

	bool isOver() const;

	void onStep();

/***************************************************************************/

private:

/***************************************************************************/

	std::unique_ptr < Player > m_first;

	std::unique_ptr < Player > m_second;

	std::unique_ptr< Field > m_field;

	bool m_step;

	bool m_isOver;

/***************************************************************************/

}; // class Game

/***************************************************************************/

inline Field &
Game::getField() const
{
	return * m_field;
}

/***************************************************************************/

inline bool 
Game::isOver() const
{
	return m_isOver;
}

inline void
Game::onStep()
{
	m_step = m_step ? false : true;

}

/***************************************************************************/

#endif // !__GAME_HPP__
