#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include "models/types/sml_02_point.h"

class Router;

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);

    QString programFilePath() const;
    void setProgramFilePath(const QString &programFilePath);

    double transitionVelocity() const;
    void setTransitionVelocity(double transitionVelocity);

    QStringList program() const;
    void setProgram(const QStringList &program);

    QList<SML02Point> points() const;
    void setPoints(const QList<SML02Point> &points);

private:
    QString m_programFilePath;
    double m_transitionVelocity;
    QStringList m_program;
    QList<SML02Point> m_points;

    friend class Router;

signals:

public slots:
};

#endif // REPOSITORY_H
