#ifndef FIND_POINTS_INTERACTOR_H
#define FIND_POINTS_INTERACTOR_H

#include <QList>

#include "models/types/sml_02_point.h"

class FindPointsInteractor
{
public:
    FindPointsInteractor();

    QList<SML02Point> execute(QStringList program);


};

#endif // FIND_POINTS_INTERACTOR_H
