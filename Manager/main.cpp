#include <QCoreApplication>
#include <QObject>
#include <iostream>
#include "manager.h"

void signalHandler(int signal)
{
    if (signal == SIGINT)
    {
        qApp->quit();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDir rootDir = a.applicationDirPath();
    if (rootDir.cd(".."))
    {
        std::cout << "Application located." << std::endl;
    }
    Manager manager(rootDir.path());

    QObject::connect(&a, SIGNAL(aboutToQuit()), &manager, SLOT(terminate()));
    signal(SIGINT, signalHandler);
    return a.exec();
}
