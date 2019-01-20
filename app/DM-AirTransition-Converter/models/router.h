#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QRegularExpression>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include "models/repository/repository.h"
#include "models/services/load_7kam_program/load_7kam_program_interactor.h"
#include "models/services/find_points/find_points_interactor.h"
#include "models/services/replace_air_transitions/replace_air_transitions_interactor.h"

class Router : public QObject
{
    Q_OBJECT
public:
    static Router& getInstance();
    ~Router();

     Repository* getRepository();

     void read7kamFile(QString filePath);

     void replaceAirTransitions(double velocity);

private:
    explicit Router(QObject *parent = nullptr);

    /// Репозиторий, хранящий текущее состояние
    QScopedPointer<Repository> m_repository;
    QScopedPointer<Load7kamProgramInteractor> m_load7kamProgram;

    /**
     * @brief Подключет слоты к сигналам полей класса
     */
    void setupConnections();

    /**
     * @brief Отключает слоты от сигналов полей класса
     */
    void resetConnections();

signals:
    void programLoaded();

public slots:

private slots:
    void onLoad7kamProgramInteractor_FileLoaded(QString content);
};

#endif // ROUTER_H
