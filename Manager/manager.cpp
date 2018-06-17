#include <iostream>
#include <fstream>
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
    if (!connection.registerService("org.fatvlady.Test.Manager"))
    {
        throw std::runtime_error("Fatal: org.fatvlady.Test.Manager service is held by another process.");
    }
    if (!connection.registerObject("/Manager", this))
    {
        throw std::runtime_error("Fatal: /Manager object is held by another process.");
    }

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

    std::ifstream file("value.txt", std::ios::binary);
    std::istream::sentry s(file);
    if (s)
    {
        file >> counter_;
        std::cout << "Resuming from value X = " << counter_ * 0.1 << std::endl;
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
        std::cout << "Waiting for a Plotter process to start and connect to dbus." << std::endl;
    }
    else if (running_)
    {
        double x = counter_ * 0.1;
        ++counter_;
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
    std::ofstream file("value.txt", std::ios::binary | std::ios::out);
    file << counter_ << std::endl; // flush
}


