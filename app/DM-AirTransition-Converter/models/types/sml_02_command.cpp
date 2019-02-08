#include "sml_02_command.h"

SML02Command::SML02Command(unsigned int index, QStringList arguments) :
    m_index(index),
    m_arguments(arguments)
{

}

SML02Command::SML02Command(QString cmd)
{
    QStringList splittedLineBySpace = cmd.split(QRegExp(" "), QString::SkipEmptyParts);
    if(splittedLineBySpace.isEmpty())
    {
        QMessageBox(QMessageBox::Critical, "Invalid argument", "Команда не распознана").exec();
        throw std::invalid_argument("Команда не распознана");
    }

    QString rawIndex = splittedLineBySpace.first();
    QString rawParams = cmd.remove(QRegExp("^" + rawIndex + "( )*"));
    QStringList params = rawParams.split(QRegExp(","));

    bool res = false;
    unsigned int index = rawIndex.toUInt(&res);
    if(!res) {
        QMessageBox(QMessageBox::Critical, "Invalid argument", "Не распознан индекс команды").exec();
        throw std::invalid_argument("Не распознан индекс команды");
    }

    m_index = index;
    m_arguments = params;
}

unsigned int SML02Command::index() const
{
    return m_index;
}

void SML02Command::setIndex(unsigned int index)
{
    m_index = index;
}

QStringList SML02Command::arguments() const
{
    return m_arguments;
}

void SML02Command::setArguments(const QStringList &arguments)
{
    m_arguments = arguments;
}

QString SML02Command::toString()
{
    return QString::number(m_index) + " " + m_arguments.join(",");
}
