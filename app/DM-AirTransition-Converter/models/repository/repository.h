#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

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

private:
    QString m_programFilePath;
    double m_transitionVelocity;
    QStringList m_program;

    friend class Router;

signals:

public slots:
};

#endif // REPOSITORY_H
