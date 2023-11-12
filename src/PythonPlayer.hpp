#pragma once
#include "PyInterpreter.hpp"

class Player;
enum class Action;

class PythonPlayer
{
public:
    PythonPlayer(PyInterpreter *interpPython);
    ~PythonPlayer();

    void SetupPlayer();
    void CreatePlayer(Player *player, const char *scriptName);

    Action ChoseAction(Player *player, const char *scriptName);

private:
    PyObject *m_playerInstance;
};
