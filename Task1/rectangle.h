#pragma once

#include "ishape.h"

class Rectangle : public IShape
{
public:
    Rectangle(const double& sideLenght1, const double& sideLength2)
    {
        m_sideLength1 = sideLenght1;
        m_sideLength2 = sideLength2;
    }

    double Area() override
    {
        return m_sideLength1 * m_sideLength2;
    }

private:
    double m_sideLength1, m_sideLength2;
};
