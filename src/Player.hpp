#pragma once 
#include <string>
#include "PythonPlayer.hpp"

enum class Action
{
    NOTHING,
    ATTACK,
    DEFEND,
    RUN,
    ERROR,
};

class Player
{
public:
    Player(const char *scriptName);
    ~Player();

    void SetupPlayer(PythonPlayer *pythonPlayer);

    void SetName(const char* name) { this->m_name = name; };
    void SetHealth(int health) { this->m_health = health; };
    void SetDamage(int damage) { this->m_damage = damage; };
    void SetArmor(int armor) { this->m_armor = armor; };
    void SetSpeed(int speed) { this->m_speed = speed; };
    void SetLevel(int level) { this->m_level = level; };
    void SetExperience(int xp) { this->m_experience = xp; };

    std::string GetName() { return m_name; };
    const int& GetPlayerID() { return m_playerID; };
    int GetHealth() { return m_health; };
    int GetDamage() { return m_damage; };
    int GetArmor() { return m_armor; };
    int GetSpeed() { return m_speed; };
    int GetLevel() { return m_level; };
    int GetExperience() { return m_experience; };

    Action ChoseAction();

private:
    const char* m_scriptName;
    int m_playerID = -1;
    std::string m_name;
    int m_health;
    int m_damage;
    int m_armor;
    int m_speed;
    int m_level;
    int m_experience;

    PythonPlayer *m_pythonPlayer;

};
