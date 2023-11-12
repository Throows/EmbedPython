#include "Player.hpp"
#include <iostream>

Player::Player(const char *scriptName) : m_scriptName(scriptName)
{
}

Player::~Player()
{
}

void Player::SetupPlayer(PythonPlayer *pythonPlayer)
{
    this->m_pythonPlayer = pythonPlayer;
    this->m_pythonPlayer->CreatePlayer(this, m_scriptName);
}

Action Player::ChoseAction()
{   
    Action action = this->m_pythonPlayer->ChoseAction(this, m_scriptName);
    return static_cast<Action>(action);
}
