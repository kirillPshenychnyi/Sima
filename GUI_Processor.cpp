#include "GUI_Processor.hpp"
#include "globals.hpp"

void
drawPoints( HDC _hdc, Field::Points _points )
{
	HBRUSH brush = CreateSolidBrush(RGB(150, 166, 255));

	for (auto pointIt : _points)
	{
		if (pointIt.getStatus() == Point::PointStatus::Filled)
			SelectObject( _hdc ,brush);
		Ellipse(_hdc, pointIt.getX(), pointIt.getY(), pointIt.getX() + Globals::diameter, pointIt.getY() + Globals::diameter);
		
		SelectObject(_hdc, GetStockObject(NULL_BRUSH));
	}
}

void drawLine(HDC _hdc, const Point::Point & _first, const Point::Point & _second)
{
	MoveToEx(_hdc, _first.getX(), _first.getY(), NULL);
}
