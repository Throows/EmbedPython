#include "Player.hpp"

#include <iostream>

#include "PythonPlayer.hpp"

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
    this->m_pythonPlayer->SetPlayerData(this);
    std::cout << "Player " << this->m_name << " created with ID " << this->m_playerID << std::endl;
}

Action Player::ChoseAction()
{   
    if (this->m_playerID == -1) return Action::ERROR;
    return this->m_pythonPlayer->ChoseAction(this);  
}

void Player::Play(Action action, Player *player)
{
    switch (action)
    {
    case Action::ATTACK:
        this->m_pythonPlayer->Attack(this);
        player->SetHealth(player->GetHealth() - this->m_damage);
        break;
    case Action::DEFEND:
        this->m_pythonPlayer->Defend(this);
        player->SetHealth(player->GetHealth() + player->GetDamage() - this->m_armor);
        break;
    case Action::RUN:
        this->m_pythonPlayer->Run(this);
        break;
    default:
        this->m_pythonPlayer->Nothing(this);
        break;
    }
}
