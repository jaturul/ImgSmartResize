#ifndef SEAM_H
#define SEAM_H

#include <utility>
#include "ImageProcessing/containers/Orientation.h"

struct Coord2D
{
public:

	Coord2D(unsigned row, unsigned col): m_rowCol(row,col) {}

	unsigned Row()
	{
		return m_rowCol.first;
	}

	unsigned Col()
	{
		return m_rowCol.second;
	}

private:
	std::pair<unsigned, unsigned> m_rowCol;
};

struct Seam
{
public:
	Seam(Orientation orientation): m_orientation(orientation) {}

	void addElement(Coord2D point)
	{
		m_elements.push_back(point);
	}

	Coord2D at(unsigned index) const
	{
		if (index >= m_elements.size())
		{
			throw "Wrong index provided!";
		}

		return m_elements.at(index);
	}

	int size() const
	{
		return m_elements.size();
	}

	Orientation orientation() const
	{
		return m_orientation;
	}

private:
	Orientation m_orientation;
	std::vector<Coord2D> m_elements;

};

#endif
