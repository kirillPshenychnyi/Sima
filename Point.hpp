#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "PointStatus.hpp"
#include <vector>

namespace Point
{

class Point
{

/***************************************************************************/

public:

/***************************************************************************/

	typedef std::vector< const Point * >::const_iterator PointIterator;

	struct Connections;

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

	Connections getConnections() const;

/***************************************************************************/

private:

/***************************************************************************/

	PointStatus m_status;

	const int m_x;

	const int m_y;

	std::vector < const Point * > m_connections;

/***************************************************************************/

};

/***************************************************************************/

struct Point::Connections
{
	Connections( Point::PointIterator _begin, Point::PointIterator _end )
		:	m_begin( _begin )
		,	m_end( _end )
	{}

	Point::PointIterator begin() const
	{
		return m_begin;
	}

	Point::PointIterator end() const
	{
		return m_end;
	}

	Point::PointIterator m_begin, m_end;
	
};

/***************************************************************************/

inline Point::Connections
Point::getConnections() const
{
	return Connections( m_connections.begin(), m_connections.end() );
}

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

} // namespace Point


#endif // __POINT_HPP__
