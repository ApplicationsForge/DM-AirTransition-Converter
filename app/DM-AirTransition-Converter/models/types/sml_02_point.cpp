#include "sml_02_point.h"

SML02Point::SML02Point(unsigned int index, double x, double y, double z) :
    m_index(index),
    m_x(x),
    m_y(y),
    m_z(z)
{

}

unsigned int SML02Point::index() const
{
    return m_index;
}

void SML02Point::setIndex(unsigned int index)
{
    m_index = index;
}

double SML02Point::x() const
{
    return m_x;
}

void SML02Point::setX(double x)
{
    m_x = x;
}

double SML02Point::y() const
{
    return m_y;
}

void SML02Point::setY(double y)
{
    m_y = y;
}

double SML02Point::z() const
{
    return m_z;
}

void SML02Point::setZ(double z)
{
    m_z = z;
}
