#include "Application.hpp"
#include "mygame.hpp"
#include <iostream>

Application *appInstance = nullptr;

Application::Application(const char *scriptPath) : interpPython(scriptPath)
{
    appInstance = this;
}

Application::~Application()
{
}

void Application::Initialize()
{
    interpPython.Initialize();
    players.push_back(new Player("PlayerOne"));
    players[0]->SetupPlayer(&pythonPlayer);
    players.push_back(new Player("PlayerTwo"));
    players[1]->SetupPlayer(&pythonPlayer);
}

void Application::Uninitialize()
{
    pythonPlayer.UninitializePlayer();
    delete players[0];
    delete players[1];
    players.clear();
    interpPython.Uninitialize();
}

void Application::Run()
{
    Action playerAction;
    while (players[0]->GetHealth() > 0 && players[1]->GetHealth() > 0) {
        playerAction = players[this->currentPlayer]->ChoseAction();
        int previous = (this->currentPlayer - 1) % 2;
        players[this->currentPlayer]->Play(playerAction, players[1]);
        this->currentPlayer++;
        this->currentPlayer%=2;
    }

    if (players[0]->GetHealth() <= 0)
        std::cout << "Player " << players[1]->GetName() << " won ! (HP: " << players[1]->GetHealth() << ")" << std::endl;
    else
        std::cout << "Player " << players[0]->GetName() << " won ! (HP: " << players[0]->GetHealth() << ")" << std::endl;
}

std::string Application::GetPlayingPlayerName()
{
    return players[this->currentPlayer]->GetName();
}
