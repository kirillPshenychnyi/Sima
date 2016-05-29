#include "GUI_Processor.hpp"

void
drawPoints( HDC _hdc, Field::Points _points )
{
	// TODO draw an elips 

	for (auto pointIt : _points)
		Ellipse( _hdc, pointIt.getX(), pointIt.getY(), pointIt.getX() + 15, pointIt.getY() + 15 );
		
}