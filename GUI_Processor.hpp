#ifndef __GUI__PROCESSOR_HPP__
#define	__GUI__PROCESSOR_HPP__

#include <windows.h>
#include "Field.hpp"

void drawPoints( HDC _hdc, Field::Points _points  );

void drawLine( HDC _hdc, const Point::Point & _first, const Point::Point & _second);

#endif // !__GUI__PROCCESOR_HPP__
