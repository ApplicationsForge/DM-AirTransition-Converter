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

void Router::replaceAirTransitions(double velocity)
{
    m_repository->setTransitionVelocity(velocity);

    FindPointsInteractor findPoints;
    m_repository->setPoints(findPoints.execute(m_repository->program()));

    ReplaceAirTransitionsInteractor replaceAirTransitions;
    m_repository->setProgram(replaceAirTransitions.execute(m_repository->program(), m_repository->points(), m_repository->transitionVelocity()));

    //save to file
    QString filename = QFileDialog::getSaveFileName(nullptr, "Выберите место сохранения прогрммы", "", "*.7kam");
    if(filename.length() > 0)
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "error while writing";
            return;
        }

        QTextStream out(&file);
        out.setCodec("utf-8");
        out << m_repository->program().join("\n");// write(m_repository->program().join("\n").toUtf8());
        file.close();
    }
}

void Router::onLoad7kamProgramInteractor_FileLoaded(QString content)
{
    QStringList program = content.split(QRegularExpression{R"-((\r\n?|\n))-"}, QString::SkipEmptyParts);
    m_repository->setProgram(program);
    emit programLoaded();
}

