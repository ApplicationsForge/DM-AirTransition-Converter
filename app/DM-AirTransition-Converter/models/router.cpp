#include "router.h"

Router::Router(QObject *parent) :
    QObject(parent),
    m_repository(new Repository(this)),
    m_load7kamProgram(new Load7kamProgramInteractor(this))
{
    setupConnections();
}

Router::~Router()
{
    resetConnections();
}

Router &Router::getInstance()
{
    static QScopedPointer<Router> m_instance;
    if(m_instance.data() == nullptr)
    {
        m_instance.reset( new Router() );
    }
    return *m_instance;
}

Repository *Router::getRepository()
{
    return m_repository.data();
}

void Router::setupConnections()
{
    QObject::connect(m_load7kamProgram.data(), SIGNAL(fileLoaded(QString)), this, SLOT(onLoad7kamProgramInteractor_FileLoaded(QString)));
}

void Router::resetConnections()
{
    QObject::disconnect(m_load7kamProgram.data(), SIGNAL(fileLoaded(QString)), this, SLOT(onLoad7kamProgramInteractor_FileLoaded(QString)));
}

void Router::read7kamFile(QString filePath)
{
    m_repository->setProgramFilePath(filePath);
    m_load7kamProgram.data()->execute(filePath);
}

void Router::replaceAirTransitions()
{
    FindPointsInteractor findPoints;
    m_repository->setPoints(findPoints.execute(m_repository->program()));

    QList<SML02Point> points = m_repository->points();
    for(auto point : points)
    {
        qDebug() << point.index() << point.x() << point.y() << point.z();
    }
}

void Router::onLoad7kamProgramInteractor_FileLoaded(QString content)
{
    QStringList program = content.split(QRegularExpression{R"-((\r\n?|\n))-"});
    m_repository->setProgram(program);
    emit programLoaded();
}

