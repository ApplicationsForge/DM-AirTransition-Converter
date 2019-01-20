#include "replace_air_transitions_interactor.h"

ReplaceAirTransitionsInteractor::ReplaceAirTransitionsInteractor()
{

}

QStringList ReplaceAirTransitionsInteractor::execute(QStringList program, QList<SML02Point> points, double velocity)
{
    QStringList result = QStringList();

    for(auto line : program)
    {
        QStringList splittedLineBySpace = line.split(QRegExp(" "), QString::SkipEmptyParts);
        if(!splittedLineBySpace.isEmpty())
        {
            QString index = splittedLineBySpace.first();
            QString params = splittedLineBySpace.last();
            if(index.toInt() == 0)
            {
                QStringList splittedParams = params.split(QRegExp(","), QString::SkipEmptyParts);
                bool needToReplace = false;
                for(auto param : splittedParams)
                {
                    if(param == "^")
                    {
                        needToReplace = true;
                        break;
                    }
                }

                if(needToReplace)
                {
                    QStringList replacedAirTransition = this->replaceAirTransition(splittedParams, points, velocity);
                    for(auto command : replacedAirTransition)
                    {
                        result.append(command);
                    }
                }
                else
                {
                    result.append(line);
                }
            }
            else
            {
                result.append(line);
            }
        }
    }

    return result;
}

QStringList ReplaceAirTransitionsInteractor::replaceAirTransition(QStringList params, QList<SML02Point> points, double velocity)
{
    QStringList result = QStringList();
    if(params.length() >= 4)
    {
        unsigned int beginPointIndex = params[0].toUInt();
        unsigned int endPointIndex = params[1].toUInt();
        double height = params[3].toDouble();
        double cuttingVelocity = 5.0;
        if(params.length() == 5)
        {
            cuttingVelocity = params[4].toDouble();
        }

        QString firstCommand = "4 0.00,0.00," + QString::number(height) + "," + QString::number(cuttingVelocity);
        QString secondCommand = this->buildSecondCommand(beginPointIndex, endPointIndex, points, velocity);
        QString thirdCommand = "4 0.00,0.00," + QString::number(-1 * height) + "," + QString::number(cuttingVelocity);

        result.append(firstCommand);
        result.append(secondCommand);
        result.append(thirdCommand);
    }
    return result;
}

QString ReplaceAirTransitionsInteractor::buildSecondCommand(unsigned int beginPointIndex, unsigned int endPointIndex, QList<SML02Point> points, double velocity)
{
    QString result = "";

    if(int (beginPointIndex) < points.length() && int (endPointIndex) < points.length())
    {
        SML02Point beginPoint = points[int (beginPointIndex)];
        SML02Point endPoint = points[int (endPointIndex)];

        double dx = endPoint.x() - beginPoint.x();
        double dy = endPoint.y() - beginPoint.y();
        double dz = 0.0;

        result = "4 " + QString::number(dx) + "," + QString::number(dy) + "," + QString::number(dz) + "," + QString::number(velocity);
    }

    return result;
}
