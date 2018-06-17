#include <iostream>
#include <thread>
#include <fstream>

#include "manager.h"

Manager::Manager(QString rootDir) : rootDir_(rootDir)
{
    arrow = new org::fatvlady::Test::ArrowInterface("org.fatvlady.Test", "/Arrow",
                           QDBusConnection::sessionBus(), this);
    //plotter.start(rootDir_.absoluteFilePath("Plotter/Plotter.app"));
    startTimer(1000);
}

void Manager::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    if(!arrow->isValid())
    {
        std::cout << "Waiting for a process to start and connect to dbus." << std::endl;
    }
    else
    {
        double x = counter * 0.1;
        ++counter;
        arrow->move(x, std::sin(x));
        std::cout << "X = " << x << " Y = " << std::sin(x) << std::endl;
    }
}

void Manager::terminate()
{
    std::cout << "Terminating child processes..." << std::endl;
    plotter.terminate();
}
