#ifndef MANAGER_H
#define MANAGER_H

#include <QDir>
#include <QProcess>

class Manager
{
public:
    Manager(QString rootDir);
    void run();
private: // METHODS
    void tick();

signals:


private: // MEMBERS
    QDir rootDir_;
    QProcess plotter;
    QProcess controller;
};

#endif // MANAGER_H
