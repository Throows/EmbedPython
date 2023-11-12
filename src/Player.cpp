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
    this->m_playerID = this->m_pythonPlayer->CreatePlayer(this, m_scriptName);
    std::cout << "Player " << this->m_name << " created with ID " << this->m_playerID << std::endl;
    this->m_pythonPlayer->SetPlayerData(this);
}

Action Player::ChoseAction()
{   
    if (this->m_playerID == -1) return Action::ERROR;
    return this->m_pythonPlayer->ChoseAction(this);  
}
