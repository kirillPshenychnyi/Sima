#include "Game.hpp"

Game::Game(const std::string & _first, const std::string & _second)
{
	m_first = std::make_unique< Player >(_first);

	m_second = std::make_unique< Player >(_second);

	m_field = std::make_unique< Field >();	
}
