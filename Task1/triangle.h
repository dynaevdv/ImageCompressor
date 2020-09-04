#pragma once

#include <cmath>

#include "ishape.h"

class Triangle : public IShape
{
public:
    Triangle(const double& sideLength1, const double& sideLength2,
             const double& sideLength3)
    {
        m_sideLength1 = sideLength1;
        m_sideLength2 = sideLength2;
        m_sideLength3 = sideLength3;
    }

    double Area() override
    {
        double p = getHalfOfPerimeter();

        return std::sqrt(p * (p - m_sideLength1) * (p - m_sideLength2) * (p - m_sideLength3));
    }

private:
    double m_sideLength1, m_sideLength2, m_sideLength3;

    double getHalfOfPerimeter()
    {
        return (m_sideLength1 + m_sideLength2 + m_sideLength3) / 2;
    }
};
