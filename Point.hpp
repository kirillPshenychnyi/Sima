#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "PointStatus.hpp"
#include <unordered_set>

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

	bool operator == (const Point & _point) const;

	void setStatus(PointStatus _status); 

	void addConnection( const Point & _point );

	bool hasConnection( const Point & _point ) const;

/***************************************************************************/

private:

/***************************************************************************/

	PointStatus m_status;

	const int m_x;

	const int m_y;

	std::unordered_set < const Point * > m_connections;

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

inline bool
Point::hasConnection(const Point & _point) const
{
	return m_connections.find(&_point) != m_connections.end();
}

/***************************************************************************/
} // namespace Point

#endif // __POINT_HPP__
