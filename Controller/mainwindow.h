#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "manager_interface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void timerEvent(QTimerEvent*);
    ~MainWindow();

public Q_SLOTS:
    void startAnimate();
    void stopAnimate();

private:
    org::fatvlady::Test::ManagerInterface *manager;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
