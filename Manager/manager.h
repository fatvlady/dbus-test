#ifndef MANAGER_H
#define MANAGER_H

#include <QDir>
#include <QProcess>
#include "arrow_adaptor.h"

class Manager
{
public:
    Manager(QString rootDir);
    void run();
private: // METHODS
    void tick();

signals:


private: // MEMBERS
    ArrowInterfaceAdaptor *arrow;
    QDir rootDir_;
    QProcess plotter;
    QProcess controller;
};

#endif // MANAGER_H
