#include "find_points_interactor.h"

FindPointsInteractor::FindPointsInteractor()
{

}

QList<SML02Point> FindPointsInteractor::execute(QStringList program)
{
    QList<SML02Point> result = QList<SML02Point>();
    for(auto line : program)
    {
        QStringList splittedLineBySpace = line.split(QRegExp(" "), QString::SkipEmptyParts);
        if(!splittedLineBySpace.isEmpty())
        {
            QString index = splittedLineBySpace.first();
            QString params = splittedLineBySpace.last();
            if(index.toInt() == 250) {
                QStringList splittedParams = params.split(QRegExp(","), QString::SkipEmptyParts);
                if(splittedParams.size() == 3)
                {
                    result.append(SML02Point((unsigned int) result.size(),
                                             splittedParams[0].toDouble(),
                                             splittedParams[1].toDouble(),
                                             splittedParams[2].toDouble()));
                }
            }
        }
    }
    return  result;
}
