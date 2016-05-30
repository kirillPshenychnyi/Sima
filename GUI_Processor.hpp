#ifndef __GUI__PROCESSOR_HPP__
#define	__GUI__PROCESSOR_HPP__

#include <windows.h>
#include "Field.hpp"

class GUIProcessor
{

/***************************************************************************/

public:

/***************************************************************************/

	GUIProcessor();

	GUIProcessor( const GUIProcessor & ) = delete;

	GUIProcessor operator = ( const GUIProcessor &) = delete;

	~GUIProcessor();

	void drawPoints(HDC _hdc, Field::Points _points);

	void drawLine(HDC _hdc, const Point::Point & _first, const Point::Point & _second);

/***************************************************************************/

private:

/***************************************************************************/

	HPEN m_first;

	HPEN m_second;

	HBRUSH m_brush;

	bool m_step;

/***************************************************************************/

};

/***************************************************************************/

#endif // !__GUI__PROCCESOR_HPP__
