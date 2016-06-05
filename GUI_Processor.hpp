#ifndef __GUI__PROCESSOR_HPP__
#define	__GUI__PROCESSOR_HPP__

#include <windows.h>
#include "Field.hpp"
#include "Player.hpp"

class GUIProcessor
{

/***************************************************************************/

public:

/***************************************************************************/

	GUIProcessor();

	GUIProcessor( const GUIProcessor & ) = delete;

	GUIProcessor operator = ( const GUIProcessor &) = delete;

	~GUIProcessor();

	void drawPoints(HDC _hdc, Field::Points _points) const ;

	bool drawLine(HDC _hdc, Point::Point & _first, Point::Point & _second);

	static void printWinner( HWND _hwnd, std::string const & _name );

	void printTriangle(HDC _hdc, const Player::triangle & _triangle) const;

/***************************************************************************/

private:

/***************************************************************************/

	void connectPoints(HDC _hdc, const Point::Point & _first, const Point::Point & _second) const;

/***************************************************************************/

private:

/***************************************************************************/

	HPEN m_first;

	HPEN m_second;

	HPEN m_triangle;

	HBRUSH m_brush;

	bool m_step;

/***************************************************************************/

};

/***************************************************************************/

#endif // !__GUI__PROCCESOR_HPP__
