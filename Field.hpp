#ifndef __FIELD_HPP__
#define __FIELD_HPP__

/***************************************************************************/

#include <unordered_set>
#include "Point.hpp"

/***************************************************************************/

class Field
{

/***************************************************************************/

public:

/***************************************************************************/

	typedef std::unordered_set< Point::Point, Point::Hasher >::const_iterator PointIterator;

	struct Points;

/***************************************************************************/

public:

/***************************************************************************/

	Field();

	Field(const Field &) = delete;

	Field & operator = ( const Field & ) = delete;

	Points getPoints() const;

/***************************************************************************/

private:

/***************************************************************************/

	void addPoint();

/***************************************************************************/

private:

/***************************************************************************/

	std::unordered_set< Point::Point, Point::Hasher > m_points;

/***************************************************************************/
};

struct Field::Points
{
	Points(Field::PointIterator _begin, Field::PointIterator _end)
		: m_begin(_begin)
		, m_end(_end)
	{}

/***************************************************************************/

	Field::PointIterator begin() const
	{
		return m_begin;
	}

	Field::PointIterator end() const
	{
		return m_end;
	}

/***************************************************************************/

	Field::PointIterator m_begin;

	Field::PointIterator m_end;
};

/***************************************************************************/

inline Field::Points
Field::getPoints() const
{
	return Points(m_points.begin(), m_points.end());
}

/***************************************************************************/

#endif // !__FIELD_HPP__
