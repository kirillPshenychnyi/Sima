#include "Game.hpp"
#include "resource.h"

Game::Game(const std::string & _first, const std::string & _second)
{
	m_first = std::make_unique< Player >(_first);

	m_second = std::make_unique< Player >(_second);

	m_field = std::make_unique< Field >();	

	m_step = true;

	m_isOver = false;
}


/***************************************************************************/


void 
Game::addPoint(const Point::Point & _point)
{
	m_step ? m_first->addPoint(_point) : m_second->addPoint( _point );
	
	m_step = m_step ? false : true;

}


/***************************************************************************/

std::string 
Game::getWinner()
{
	std::string winner = "";

	if (m_first->isTriangle())
		winner = m_second->getName();

	else if ( m_second->isTriangle() )
		winner = m_first->getName();
	
	if ( !winner.empty() )
		m_isOver = true;

	return winner;
}

/***************************************************************************/