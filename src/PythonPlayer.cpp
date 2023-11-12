#include "PythonPlayer.hpp"
#include <iostream>
#include "Player.hpp"

PythonPlayer::PythonPlayer()
{
}

PythonPlayer::~PythonPlayer()
{
}

void PythonPlayer::SetupPlayer()
{
}

int PythonPlayer::CreatePlayer(Player *player, const char *scriptName)
{
    PyObject *playerModule, *playerObjectAttr, *playerObject;
    int playerID = -1;
    playerModule = PyImport_ImportModule(scriptName);
    if (playerModule == nullptr) {
        std::cout << "Error while importing the " << scriptName << " module\n";
        PyErr_Print();
        return playerID;
    }

    playerObjectAttr = PyObject_GetAttrString(playerModule, "Player");
    if (playerObjectAttr != nullptr && PyCallable_Check(playerObjectAttr)) {
        playerObject = PyObject_CallObject(playerObjectAttr, NULL);
        if (playerObject != nullptr) {
            this->m_playersObject.push_back(playerObject);
            playerID = this->m_playersObject.size() - 1;
        } else {
            std::cout << "Error while calling the Player object\n";
            PyErr_Print();
        }
        Py_DECREF(playerObjectAttr);
    } else {
        std::cout << "Error while getting the Player attribute\n";
        PyErr_Print();
    }
    Py_DECREF(playerModule);
    return playerID;
}

Action PythonPlayer::ChoseAction(Player *player)
{
    Action action = Action::ERROR;
    PyObject *actionFunc, *actionResult;

    actionFunc = PyUnicode_DecodeFSDefault("ChoseAction");
    int id = player->GetPlayerID();
    if (actionFunc != nullptr) {
        actionResult = PyObject_CallMethodObjArgs(this->m_playersObject[id], actionFunc, NULL);
        if (actionResult != nullptr) {
            if (PyLong_Check(actionResult)) {
                int actionRaw = PyLong_AsLong(actionResult);
                action = static_cast<Action>(actionRaw);
            } else {
                std::cout << "Error while getting the ChoseAction function\n";
                PyErr_Print();
            }
            Py_DECREF(actionResult);
        } else {
            std::cout << "Error while getting the ChoseAction function\n";
            PyErr_Print();
        }
        Py_DECREF(actionFunc);
    } else {
        std::cout << "Error while getting the ChoseAction function\n";
        PyErr_Print();
    }
    return action;
}

void PythonPlayer::Attack(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;
    PyObject *playerModule = this->m_playersObject[playerID];
    PyObject *attackFunc, *attackResult;
    attackFunc = PyUnicode_DecodeFSDefault("DoAttack");
    if (attackFunc != nullptr) {
        attackResult = PyObject_CallMethodObjArgs(playerModule, attackFunc, NULL);
        if (attackResult != nullptr) {
            if (PyBool_Check(attackResult)) {
                bool succed = PyLong_AsLong(attackResult);
            } else {
                std::cout << "Error while getting the Attack function\n";
                PyErr_Print();
            }
            Py_DECREF(attackResult);
        } else {
            std::cout << "Error while getting the Attack function\n";
            PyErr_Print();
        }
        Py_DECREF(attackFunc);
    } else {
        std::cout << "Error while getting the Attack function\n";
        PyErr_Print();
    }
}

void PythonPlayer::Defend(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;
    PyObject *playerModule = this->m_playersObject[playerID];
    PyObject *attackFunc, *attackResult;
    attackFunc = PyUnicode_DecodeFSDefault("DoDefend");
    if (attackFunc != nullptr) {
        attackResult = PyObject_CallMethodObjArgs(playerModule, attackFunc, NULL);
        if (attackResult != nullptr) {
            if (PyBool_Check(attackResult)) {
                bool succed = PyLong_AsLong(attackResult);
            } else {
                std::cout << "Error while getting the Attack function\n";
                PyErr_Print();
            }
            Py_DECREF(attackResult);
        } else {
            std::cout << "Error while getting the Attack function\n";
            PyErr_Print();
        }
        Py_DECREF(attackFunc);
    } else {
        std::cout << "Error while getting the Attack function\n";
        PyErr_Print();
    }
}

void PythonPlayer::Run(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;
    PyObject *playerModule = this->m_playersObject[playerID];
    PyObject *attackFunc, *attackResult;
    attackFunc = PyUnicode_DecodeFSDefault("DoRun");
    if (attackFunc != nullptr) {
        attackResult = PyObject_CallMethodObjArgs(playerModule, attackFunc, NULL);
        if (attackResult != nullptr) {
            if (PyBool_Check(attackResult)) {
                bool succed = PyLong_AsLong(attackResult);
            } else {
                std::cout << "Error while getting the Attack function\n";
                PyErr_Print();
            }
            Py_DECREF(attackResult);
        } else {
            std::cout << "Error while getting the Attack function\n";
            PyErr_Print();
        }
        Py_DECREF(attackFunc);
    } else {
        std::cout << "Error while getting the Attack function\n";
        PyErr_Print();
    }
}

void PythonPlayer::Nothing(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;
    PyObject *playerModule = this->m_playersObject[playerID];
    PyObject *attackFunc, *attackResult;
    attackFunc = PyUnicode_DecodeFSDefault("DoNothing");
    if (attackFunc != nullptr) {
        attackResult = PyObject_CallMethodObjArgs(playerModule, attackFunc, NULL);
        if (attackResult != nullptr) {
            if (PyBool_Check(attackResult)) {
                bool succed = PyLong_AsLong(attackResult);
            } else {
                std::cout << "Error while getting the Attack function\n";
                PyErr_Print();
            }
            Py_DECREF(attackResult);
        } else {
            std::cout << "Error while getting the Attack function\n";
            PyErr_Print();
        }
        Py_DECREF(attackFunc);
    } else {
        std::cout << "Error while getting the Attack function\n";
        PyErr_Print();
    }
}

void PythonPlayer::SetPlayerData(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;
    PyObject *playerModule = this->m_playersObject[playerID];
    PyObject *gameDataDict;
    gameDataDict = PyObject_GetAttrString(playerModule, "PlayerData");
    if (gameDataDict && PyDict_Check(gameDataDict)) {
        PyObject *key, *value;
        Py_ssize_t pos = 0;

        while (PyDict_Next(gameDataDict, &pos, &key, &value)) {
            std::string keyStr = PyUnicode_AsUTF8(key);
            if (keyStr == "Name")           player->SetName(PyUnicode_AsUTF8(value));
            else if (keyStr == "Health")    player->SetHealth(PyLong_AsLong(value));
            else if (keyStr == "Damage")    player->SetDamage(PyLong_AsLong(value));
            else if (keyStr == "Armor")     player->SetArmor(PyLong_AsLong(value));
            else if (keyStr == "Speed")     player->SetSpeed(PyLong_AsLong(value));
            else if (keyStr == "Level")     player->SetLevel(PyLong_AsLong(value));
            else if (keyStr == "Experience") player->SetExperience(PyLong_AsLong(value));
            else std::cout << "Error while getting the " << keyStr << " attribute\n";

            Py_DECREF(key);
            Py_DECREF(value);
        }
        Py_DECREF(gameDataDict);
    } else {
        std::cout << "Error while getting the PlayerData attribute\n";
        PyErr_Print();
    }
}
