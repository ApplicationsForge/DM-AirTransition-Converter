#ifndef SML_02_COMMAND_H
#define SML_02_COMMAND_H

#include <QStringList>
#include <QMessageBox>

class SML02Command
{
public:
    SML02Command(unsigned int index, QStringList arguments);
    SML02Command(QString cmd);

    unsigned int index() const;
    void setIndex(unsigned int index);

    QStringList arguments() const;
    void setArguments(const QStringList &arguments);

    QString toString();

private:
    unsigned int m_index;
    QStringList m_arguments;
};

#endif // SML_02_COMMAND_H
