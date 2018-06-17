#include <iostream>
#include <thread>

#include "manager.h"

Manager::Manager(QString rootDir) : rootDir_(rootDir)
{
}

void Manager::run()
{
    plotter.start(rootDir_.absoluteFilePath("Plotter/Plotter.app"));

    for(int i = 0; i < 40; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        tick();
    }
    plotter.terminate();
}

void Manager::tick()
{
    std::cout << "tick" << std::endl;
}
