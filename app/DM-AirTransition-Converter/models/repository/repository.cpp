#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_programFilePath(""),
    m_transitionVelocity(0.0),
    m_program(QStringList())
{

}

QString Repository::programFilePath() const
{
    return m_programFilePath;
}

void Repository::setProgramFilePath(const QString &programFilePath)
{
    m_programFilePath = programFilePath;
}

double Repository::transitionVelocity() const
{
    return m_transitionVelocity;
}

void Repository::setTransitionVelocity(double transitionVelocity)
{
    m_transitionVelocity = transitionVelocity;
}

QStringList Repository::program() const
{
    return m_program;
}

void Repository::setProgram(const QStringList &program)
{
    m_program = program;
}
