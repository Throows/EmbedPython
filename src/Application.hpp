#pragma once

#include "PythonPlayer.hpp"
#include "Player.hpp"

class Application
{
public:
    Application(const char *scriptPath);
    ~Application();

    void Initialize();
    void Uninitialize();
    void Run();

private:
    PyInterpreter interpPython;
    PythonPlayer pythonPlayer;
    std::vector<Player *> players;
};