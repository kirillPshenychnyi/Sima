#include "Game.hpp"
#include <ctime>

Game::Game(const std::string & _first, const std::string & _second)
{
	m_first = std::make_unique< Player >(_first) ;

	m_second = std::make_unique< Player >(_second) ;

}
