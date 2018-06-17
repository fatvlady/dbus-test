#include <QCoreApplication>
#include <QObject>
#include <iostream>
#include "manager.h"

void signalHandler(int signal)
{
    if (signal == SIGINT || signal == SIGTERM)
    {
        qApp->quit();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDir rootDir = a.applicationDirPath();
    rootDir.cdUp();
    Manager manager(rootDir.path());

    QObject::connect(&a, SIGNAL(aboutToQuit()), &manager, SLOT(terminate()));
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    return a.exec();
}
