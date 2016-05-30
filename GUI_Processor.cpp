#include "GUI_Processor.hpp"
#include "globals.hpp"

GUIProcessor::GUIProcessor()
{
	m_brush = CreateSolidBrush(RGB(150, 166, 255));

	m_first = CreatePen(PS_SOLID, 1, RGB(150, 166, 255));

	m_second = CreatePen(PS_SOLID, 1, RGB(220, 135, 120));

	m_step = true;

}

GUIProcessor::~GUIProcessor()
{
	DeleteObject(m_brush);
	DeleteObject(m_first);
	DeleteObject(m_second);
}


void
GUIProcessor::drawPoints( HDC _hdc, Field::Points _points ) const
{
	for (auto pointIt : _points)
	{
		if (pointIt.getStatus() == Point::PointStatus::Filled)
			SelectObject( _hdc, m_brush);
		Ellipse(_hdc, pointIt.getX(), pointIt.getY(), pointIt.getX() + Globals::diameter, pointIt.getY() + Globals::diameter);
		
		SelectObject(_hdc, GetStockObject(NULL_BRUSH));
	}
}

bool 
GUIProcessor::drawLine(HDC _hdc, Point::Point & _first, Point::Point & _second)
{
	if (_first == _second
		|| _first.getDestination() == &_second
		|| &_first == _second.getDestination())
	{
		_first.setStatus(Point::PointStatus::Empty);
		_second.setStatus(Point::PointStatus::Empty);

		return false;
	}

	m_step ? SelectObject(_hdc, m_first) : SelectObject(_hdc, m_second);

	_first.connect( & _second);

	m_step = m_step ? false : true;

	MoveToEx( _hdc, _first.getX() + Globals::diameter / 2, _first.getY() + Globals::diameter / 2, NULL);

	LineTo( _hdc, _second.getX() + Globals::diameter / 2, _second.getY() + Globals::diameter / 2);

	SelectObject(_hdc, GetStockObject(BLACK_PEN));

	return true;

}

