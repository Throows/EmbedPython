#pragma once
#include "PyInterpreter.hpp"
#include "Player.hpp"

class PythonPlayer
{
public:
    PythonPlayer();
    ~PythonPlayer();

    void SetupPlayer();
    void UninitializePlayer();
    int CreatePlayer(Player *player, const char *scriptName);
    void SetPlayerData(Player *player);

    Action ChoseAction(Player *player);
    void Attack(Player *player);
    void Defend(Player *player);
    void Run(Player *player);
    void Nothing(Player *player);

private:
    std::vector<PyObject *> m_playersObject;
};
