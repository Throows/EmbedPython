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
    void CreatePlayer(Player *player, const char *scriptName);

    Action ChoseAction(Player *player, const char *scriptName);

private:
    std::vector<PyObject *> m_playersObject;
};
