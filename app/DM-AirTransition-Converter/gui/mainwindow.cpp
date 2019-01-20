#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setupWidgets();
    this->setupConnections();
}

MainWindow::~MainWindow()
{
    this->resetConnections();
    delete ui;
}

void MainWindow::setupWidgets()
{
    ui->mainToolBar->hide();

    // установка оформления statusBar
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));

    ui->applyPushButton->setEnabled(false);
}

void MainWindow::setupConnections()
{
    Router& router = Router::getInstance();
    QObject::connect(&router, SIGNAL(programLoaded()), this, SLOT(onRouter_ProgramLoaded()));
}

void MainWindow::resetConnections()
{
    Router& router = Router::getInstance();
    QObject::disconnect(&router, SIGNAL(programLoaded()), this, SLOT(onRouter_ProgramLoaded()));
}

void MainWindow::onRouter_ProgramLoaded()
{
    ui->applyPushButton->setEnabled(true);
    ui->statusBar->showMessage("Программа загружена");

    Router& router = Router::getInstance();
    ui->filePathLineEdit->setText(router.getRepository()->programFilePath());
}

void MainWindow::on_selectFileToolButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Открыть", "", "*.7kam");
    if(path.length() > 0)
    {
        Router& router = Router::getInstance();
        router.read7kamFile(path);
    }
}

void MainWindow::on_applyPushButton_clicked()
{
    bool ok = false;
    QString velocity = ui->transitionVelocityLineEdit->text();
    double velocityValue = velocity.toDouble(&ok);
    if(ok)
    {
        Router& router = Router::getInstance();
        router.replaceAirTransitions(velocityValue);
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Значение скорости должно быть числовым.").exec();
    }
}
