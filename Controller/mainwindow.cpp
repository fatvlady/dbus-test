#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new org::fatvlady::Test::ManagerInterface("org.fatvlady.Test.Manager", "/Manager",
                           QDBusConnection::sessionBus(), this);
    startTimer(1000);
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    if(manager->isValid())
    {
        killTimer(event->timerId());
        ui->label->setText("Connected");
        stopAnimate();
    }
    else
        ui->label->setText("Disconnected");
}

void MainWindow::startAnimate()
{
    manager->start();
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void MainWindow::stopAnimate()
{
    manager->stop();
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
