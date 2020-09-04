#pragma once

#include "ishape.h"

class Square : public IShape
{
public:
    Square(const double& sideLength)
    {
        m_sideLength = sideLength;
    }

    double Area() override
    {
        return m_sideLength * m_sideLength;
    }

private:
    double m_sideLength;
};
