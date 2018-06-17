#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include "manager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDir rootDir = a.applicationDirPath();
    if (rootDir.cd(".."))
    {
        std::cout << "Application located." << std::endl;
    }
    Manager manager(rootDir.path());

    manager.run();
    return a.exec();
}
