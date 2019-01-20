#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "models/router.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void setupWidgets();
    void setupConnections();
    void resetConnections();

private slots:
    void onRouter_ProgramLoaded();

    void on_selectFileToolButton_clicked();
    void on_applyPushButton_clicked();
};

#endif // MAINWINDOW_H
