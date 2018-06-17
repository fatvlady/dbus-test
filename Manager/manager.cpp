#include <iostream>
#include <thread>

#include "manager.h"
#include "manager_adaptor.h"

#ifdef __APPLE__
#define EXTENSION ".app"
#elif _WIN32 || _WIN64
#define EXTENSION ".exe"
#else
#define EXTENSION ""
#endif

Manager::Manager(QString rootDir) : rootDir_(rootDir)
{
    arrow = new org::fatvlady::Test::ArrowInterface("org.fatvlady.Test", "/Arrow",
                           QDBusConnection::sessionBus(), this);
    QDBusConnection connection = QDBusConnection::sessionBus();
    new ManagerInterfaceAdaptor(this);
    connection.registerObject("/Manager", this);
    connection.registerService("org.fatvlady.Test.Manager");

    plotter.start(rootDir_.absoluteFilePath("Plotter/Plotter" EXTENSION));
    controller.start(rootDir_.absoluteFilePath("Controller/Controller" EXTENSION));
    plotter.waitForStarted();
    controller.waitForStarted();
    if (!plotter.isOpen() || !controller.isOpen())
    {
        std::cout << "Fatal: Failed to locate mandatory applications." << std::endl;
        terminate();
        std::abort();
    }

    startTimer(500);
}

void Manager::start()
{
    running_ = true;
}

void Manager::stop()
{
    running_ = false;
}

void Manager::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    if(!arrow->isValid())
    {
        std::cout << "Waiting for a process to start and connect to dbus." << std::endl;
    }
    else if (running_)
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
    controller.terminate();
    plotter.waitForFinished();
    controller.waitForFinished();
}
