#include "PythonPlayer.hpp"
#include <iostream>

PythonPlayer::PythonPlayer()
{
}

PythonPlayer::~PythonPlayer()
{
}

void PythonPlayer::SetupPlayer()
{
}

void PythonPlayer::UninitializePlayer()
{
    for (auto &player : this->m_playersObject) {
        Py_DECREF(player);
    }
}

int PythonPlayer::CreatePlayer(Player *player, const char *scriptName)
{
    int playerID = -1;
    PyObject *playerModule = PyImport_ImportModule(scriptName);
    if (playerModule == nullptr) {
        std::cout << "Error while importing the " << scriptName << " module\n";
        PyErr_Print();
        return playerID;
    }

    this->m_playersObject.push_back(playerModule);
    playerID = this->m_playersObject.size() - 1;
    return playerID;
}

Action PythonPlayer::ChoseAction(Player *player)
{
    int id = player->GetPlayerID();
    if (id == -1) return Action::ERROR;

    Action action = Action::ERROR;
    PyObject *actionFunc, *actionResult;
    actionFunc = PyObject_GetAttrString(this->m_playersObject[id], "OnChoseAction");
    if (actionFunc && PyCallable_Check(actionFunc)) {
        actionResult = PyObject_CallObject(actionFunc, NULL);
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

    PyObject *attackFunc, *attackResult;
    attackFunc = PyObject_GetAttrString(this->m_playersObject[playerID], "DoAttack");
    if (attackFunc != nullptr) {
        attackResult = PyObject_CallObject(attackFunc, NULL);
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
    
    PyObject *defendFunc, *defendResult;
    defendFunc = PyObject_GetAttrString(this->m_playersObject[playerID], "DoDefend");
    if (defendFunc != nullptr) {
        defendResult = PyObject_CallObject(defendFunc, NULL);
        if (defendResult != nullptr) {
            if (PyBool_Check(defendResult)) {
                bool succed = PyLong_AsLong(defendResult);
            } else {
                std::cout << "Error while getting the Defend function\n";
                PyErr_Print();
            }
            Py_DECREF(defendResult);
        } else {
            std::cout << "Error while getting the Defend function\n";
            PyErr_Print();
        }
        Py_DECREF(defendFunc);
    } else {
        std::cout << "Error while getting the Defend function\n";
        PyErr_Print();
    }
}

void PythonPlayer::Run(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;

    PyObject *runFunc, *runkResult;
    runFunc = PyObject_GetAttrString(this->m_playersObject[playerID], "DoRun");
    if (runFunc != nullptr) {
        runkResult = PyObject_CallObject(runFunc, NULL);
        if (runkResult != nullptr) {
            if (PyBool_Check(runkResult)) {
                bool succed = PyLong_AsLong(runkResult);
            } else {
                std::cout << "Error while getting the Run function\n";
                PyErr_Print();
            }
            Py_DECREF(runkResult);
        } else {
            std::cout << "Error while getting the Run function\n";
            PyErr_Print();
        }
        Py_DECREF(runkResult);
    } else {
        std::cout << "Error while getting the Run function\n";
        PyErr_Print();
    }
}

void PythonPlayer::Nothing(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;

    PyObject *nothingFunc, *nothingResult;
    nothingFunc = PyObject_GetAttrString(this->m_playersObject[playerID], "DoNothing");
    if (nothingFunc != nullptr) {
        nothingResult = PyObject_CallObject(nothingFunc, NULL);
        if (nothingResult != nullptr) {
            if (PyBool_Check(nothingResult)) {
                bool succed = PyLong_AsLong(nothingResult);
            } else {
                std::cout << "Error while getting the Nothing function\n";
                PyErr_Print();
            }
            Py_DECREF(nothingResult);
        } else {
            std::cout << "Error while getting the Nothing function\n";
            PyErr_Print();
        }
        Py_DECREF(nothingFunc);
    } else {
        std::cout << "Error while getting the Nothing function\n";
        PyErr_Print();
    }
}

void PythonPlayer::SetPlayerData(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;
    PyObject *playerStatFunc, *playerStatDict;
    playerStatFunc = PyObject_GetAttrString(this->m_playersObject[playerID], "OnCreatePlayer");
    if (playerStatFunc && PyCallable_Check(playerStatFunc)) {
        playerStatDict = PyObject_CallObject(playerStatFunc, NULL);
        if (playerStatDict != nullptr) {
            PyObject *key, *value;
            Py_ssize_t pos = 0;

            while (PyDict_Next(playerStatDict, &pos, &key, &value)) {
                std::string keyStr = PyUnicode_AsUTF8(key);
                if (keyStr == "Name")           player->SetName(PyUnicode_AsUTF8(value));
                else if (keyStr == "Health")    player->SetHealth(PyLong_AsLong(value));
                else if (keyStr == "Damage")    player->SetDamage(PyLong_AsLong(value));
                else if (keyStr == "Armor")     player->SetArmor(PyLong_AsLong(value));
                else if (keyStr == "Speed")     player->SetSpeed(PyLong_AsLong(value));
                else std::cout << "Error while getting the " << keyStr << " attribute\n";

                Py_DECREF(key);
                Py_DECREF(value);
            }
            Py_DECREF(playerStatDict);
        } else {
            std::cout << "Error while getting the PlayerData function\n";
            PyErr_Print();
        }
        Py_DECREF(playerStatFunc);
    } else {
        std::cout << "Error while getting the PlayerData attribute\n";
        PyErr_Print();
    }
}
