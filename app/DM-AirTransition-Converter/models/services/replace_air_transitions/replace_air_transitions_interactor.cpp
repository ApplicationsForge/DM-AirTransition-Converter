#include "replace_air_transitions_interactor.h"

ReplaceAirTransitionsInteractor::ReplaceAirTransitionsInteractor()
{

}

QStringList ReplaceAirTransitionsInteractor::execute(QStringList program, QList<SML02Point> points, double velocity)
{
    QStringList result = QStringList();

    program = this->removePoints(program);

    for(auto line : program)
    {
        result.append(this->resolveComand(line, points, velocity));
    }

    for(auto point : points)
    {
        result.append(point.toString());
    }

    return result;
}

QStringList ReplaceAirTransitionsInteractor::removePoints(QStringList program)
{
    QStringList result = {};
    for(auto line : program)
    {
        SML02Command command = SML02Command(line);
        if(command.index() != 250)
        {
            result.append(line);
        }
    }
    return result;
}

QStringList ReplaceAirTransitionsInteractor::resolveComand(QString cmd, QList<SML02Point> &points, double maxVelocity)
{
    SML02Command command = SML02Command(cmd);
    if(command.index() != 0)
    {
        return QStringList {cmd};
    }


    bool isNeedToReplace = false;
    for(auto argument : command.arguments())
    {
        if(argument == "^")
        {
            isNeedToReplace = true;
            break;
        }
    }

    if(!isNeedToReplace)
    {
        return QStringList {cmd};
    }

    QStringList replacedAirTransition = this->replaceAirTransition(command.arguments(), points, maxVelocity);
    return replacedAirTransition;
}

QStringList ReplaceAirTransitionsInteractor::replaceAirTransition(QStringList params, QList<SML02Point> &points, double velocity)
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

        SML02Point firstPoint = points[int(beginPointIndex)];
        SML02Point secondPoint = SML02Point(points.length(), firstPoint.x(), firstPoint.y(), firstPoint.z() + height);
        points.append(secondPoint);

        SML02Point fourthPoint = points[int(endPointIndex)];
        SML02Point thirdPoint = SML02Point(points.length(), fourthPoint.x(), fourthPoint.y(), fourthPoint.z() + height);
        points.append(thirdPoint);

        QString firstCommand = this->buildTTLineCommand(firstPoint.index(), secondPoint.index(), false, 0.0, cuttingVelocity);
        QString secondCommand = this->buildTTLineCommand(secondPoint.index(), thirdPoint.index(), false, 0.0, velocity);
        QString thirdCommand = this->buildTTLineCommand(thirdPoint.index(), fourthPoint.index(), false, 0.0, cuttingVelocity);

        result.append(firstCommand);
        result.append(secondCommand);
        result.append(thirdCommand);
    }
    return result;
}

QString ReplaceAirTransitionsInteractor::buildTTLineCommand(unsigned int firstPointIndex, unsigned int secondPointIndex, bool airTransition, double height, double velocity)
{
    if(airTransition)
    {
        return "0 " + QString::number(firstPointIndex) + "," + QString::number(secondPointIndex) + ",^," + QString::number(height) + "," + QString::number(velocity);
    }
    else
    {
        return "0 " + QString::number(firstPointIndex) + "," + QString::number(secondPointIndex) + ", ," + QString::number(velocity);
    }
}
