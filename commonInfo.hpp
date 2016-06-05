#ifndef __COMMON_INFO__HPP__
#define __COMMON_INFO_HPP__

#include <Windows.h>
#include "Point.hpp"
#include "Game.hpp"
#include "GUI_Processor.hpp"
#include <memory>

struct CommonInfo
{
	CommonInfo()
	{
		m_pProcessor = std::make_unique< GUIProcessor >();

		m_first = m_second = m_temp = nullptr;

	}


	PAINTSTRUCT m_ps;
	HDC m_hdc;
	std::unique_ptr < Game > m_pGame;
	std::unique_ptr < GUIProcessor > m_pProcessor;

	int m_x, m_y;

	Point::Point * m_first;
	Point::Point * m_second;
	Point::Point * m_temp;
	std::string m_winner;
	int m_click;
	std::string m_firstName, m_secondName;
};

#endif // !__COMMON_INFO__HPP__
