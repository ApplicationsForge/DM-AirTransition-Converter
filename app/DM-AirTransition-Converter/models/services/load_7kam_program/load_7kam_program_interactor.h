#ifndef LOAD_7KAM_PROGRAM_INTERACTOR_H
#define LOAD_7KAM_PROGRAM_INTERACTOR_H

#include <QObject>
#include <QString>
#include <QProgressDialog>
#include <QTime>
#include <QThread>

#include <QDebug>

#include "models/utils/file_reader.h"

class Load7kamProgramInteractor : public QObject
{
    Q_OBJECT
public:
    explicit Load7kamProgramInteractor(QObject *parent = nullptr);
    ~Load7kamProgramInteractor();

    void execute(QString filePath);

private:
    QThread* m_readerThread;

signals:
    void fileLoaded(QString content);

public slots:
    void onFileReader_SuccessfullRead(QString content);
};

#endif // LOAD_7KAM_PROGRAM_INTERACTOR_H
