#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "PointStatus.hpp"

namespace Point
{

class Point
{

/***************************************************************************/

public:

/***************************************************************************/

	Point(int _x, int _y);

	int getX() const;

	int getY() const;

	PointStatus getStatus() const;

	void connect(Point * _destination);

	const Point * getDestination() const;

	bool operator == (const Point & _point) const;

	bool operator != (const Point & _point) const;

	void setStatus(PointStatus _status); 

/***************************************************************************/

private:

/***************************************************************************/

	PointStatus m_status;

	const int m_x;

	const int m_y;

	Point * m_connected;

/***************************************************************************/

};

/***************************************************************************/

inline int
Point::getX() const
{
	return m_x;
}

/***************************************************************************/

inline int
Point::getY() const
{
	return m_y;
}

inline PointStatus Point::getStatus() const
{
	return m_status;
}


/***************************************************************************/

inline void 
Point::setStatus(PointStatus _status)
{
	m_status = _status;
}


/***************************************************************************/

}	// namespace Point

/***************************************************************************/

#endif // __POINT_HPP__
