#ifndef SML_02_POINT_H
#define SML_02_POINT_H

#include <QString>

class SML02Point
{
public:
    SML02Point(unsigned int index, double x, double y, double z);
    unsigned int index() const;
    void setIndex(unsigned int index);

    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    double z() const;
    void setZ(double z);

    QString toString();

private:
    unsigned int m_index;
    double m_x;
    double m_y;
    double m_z;
};

#endif // SML_02_POINT_H
