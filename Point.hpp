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

	Point();

	int getX() const;

	int getY() const;

	PointStatus getStatus() const;

	bool operator == (const Point & _point) const;

	void setStatus(PointStatus _status); 

/***************************************************************************/

	private:

/***************************************************************************/

	PointStatus m_status;

	const int m_x;

	const int m_y;

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

struct Hasher
{
	size_t hash(int _value) const
	{
		_value = ((_value >> 16) ^ _value) * 0x45d9f3b;
		_value = ((_value >> 16) ^ _value) * 0x45d9f3b;
		_value = ((_value >> 16) ^ _value);
		return _value;
	}

	size_t operator() (const Point & _point) const
	{
		return hash(_point.getX()) + hash(_point.getY());
	}

}; // struct Hasher

/***************************************************************************/

}	// namespace Point

/***************************************************************************/

#endif // __POINT_HPP__
