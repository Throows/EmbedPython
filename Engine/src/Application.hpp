#pragma once

#include "PythonPlayer.hpp"
#include "Player.hpp"

#ifdef __cplusplus
extern "C" {
#endif

class Application
{
public:
    Application(const char *scriptPath);
    ~Application();

    void Initialize();
    void Uninitialize();
    void Run();

    // TEST PURPOSE ONLY
    std::string GetPlayingPlayerName();

private:
    PyInterpreter interpPython;
    PythonPlayer pythonPlayer;
    std::vector<Player *> players;
    int currentPlayer = 0; 
};

extern Application *appInstance;

#ifdef __cplusplus
}
#endif