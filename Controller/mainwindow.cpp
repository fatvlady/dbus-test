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
        ui->startButton->setEnabled(true);
        ui->stopButton->setEnabled(false);
        stopAnimate();
    }
    else
        ui->label->setText("Disconnected");
}

void MainWindow::startAnimate()
{
    if (!manager->isValid())
    {
        ui->startButton->setEnabled(false);
        startTimer(1000);
        return;
    }
    manager->start();
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void MainWindow::stopAnimate()
{
    if (!manager->isValid())
    {
        ui->stopButton->setEnabled(false);
        startTimer(1000);
        return;
    }
    manager->stop();
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
