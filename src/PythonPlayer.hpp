#pragma once
#include "PyInterpreter.hpp"

class Player;
enum class Action;

class PythonPlayer
{
public:
    PythonPlayer();
    ~PythonPlayer();

    void SetupPlayer();
    int CreatePlayer(Player *player, const char *scriptName);
    void SetPlayerData(Player *player);

    Action ChoseAction(Player *player);

private:
    std::vector<PyObject *> m_playersObject;
};
