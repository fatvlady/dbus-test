#ifndef MANAGER_H
#define MANAGER_H

#include <QDir>
#include <QProcess>
#include "arrow_interface.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    Manager(QString rootDir);
    void timerEvent(QTimerEvent*);
private: // METHODS

public Q_SLOTS:
    void terminate();
    void start();
    void stop();

private: // MEMBERS
    org::fatvlady::Test::ArrowInterface *arrow;

    bool running_{};
    int counter{};
    QDir rootDir_;
    QProcess plotter;
    QProcess controller;
};

#endif // MANAGER_H
