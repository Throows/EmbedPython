#include "Application.hpp"
#include <iostream>

Application::Application(const char *scriptPath) : interpPython(scriptPath)
{
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
        playerAction = players[0]->ChoseAction();
        players[0]->Play(playerAction, players[1]);
        playerAction = players[1]->ChoseAction();
        players[1]->Play(playerAction, players[0]);
    }

    if (players[0]->GetHealth() <= 0)
        std::cout << "Player " << players[1]->GetName() << " won ! (HP: " << players[1]->GetHealth() << ")" << std::endl;
    else
        std::cout << "Player " << players[0]->GetName() << " won ! (HP: " << players[0]->GetHealth() << ")" << std::endl;
}
