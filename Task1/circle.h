#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include "ishape.h"

class Circle : public IShape
{
public:
	Circle(const double& radius)
	{
		m_radius = radius;
	}

	double Area() override
	{
		return (2 * M_PI * m_radius * m_radius);
	}
	
private:
	double m_radius;
};