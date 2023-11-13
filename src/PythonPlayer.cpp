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
   Py_CLEAR(this->m_playersObject.at(0));
   Py_CLEAR(this->m_playersObject.at(1));
   this->m_playersObject.clear();
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
    Py_INCREF(this->m_playersObject[playerID]);
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
    } else {
        std::cout << "Error while getting the ChoseAction function\n";
        PyErr_Print();
    }
    Py_XDECREF(actionFunc);
    return action;
}

void PythonPlayer::Attack(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;

    PyObject *attackFunc, *attackResult;
    attackFunc = PyObject_GetAttrString(this->m_playersObject[playerID], "DoAttack");
    if (attackFunc != nullptr && PyCallable_Check(attackFunc)) {
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
    } else {
        std::cout << "Error while getting the Attack function\n";
        PyErr_Print();
    }
    Py_XDECREF(attackFunc);
}

void PythonPlayer::Defend(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;
    
    PyObject *defendFunc, *defendResult;
    defendFunc = PyObject_GetAttrString(this->m_playersObject[playerID], "DoDefend");
    if (defendFunc != nullptr && PyCallable_Check(defendFunc)) {
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
    } else {
        std::cout << "Error while getting the Defend function\n";
        PyErr_Print();
    }
    Py_XDECREF(defendFunc);
}

void PythonPlayer::Run(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;

    PyObject *runFunc, *runResult;
    runFunc = PyObject_GetAttrString(this->m_playersObject[playerID], "DoRun");
    if (runFunc != nullptr && PyCallable_Check(runFunc)) {
        runResult = PyObject_CallObject(runFunc, NULL);
        if (runResult != nullptr) {
            if (PyBool_Check(runResult)) {
                bool succed = PyLong_AsLong(runResult);
            } else {
                std::cout << "Error while getting the Run function\n";
                PyErr_Print();
            }
            Py_DECREF(runResult);
        } else {
            std::cout << "Error while getting the Run function\n";
            PyErr_Print();
        }
    } else {
        std::cout << "Error while getting the Run function\n";
        PyErr_Print();
    }
    Py_XDECREF(runFunc);
}

void PythonPlayer::Nothing(Player *player)
{
    int playerID = player->GetPlayerID();
    if (playerID == -1) return;

    PyObject *nothingFunc, *nothingResult;
    nothingFunc = PyObject_GetAttrString(this->m_playersObject[playerID], "DoNothing");
    if (nothingFunc != nullptr && PyCallable_Check(nothingFunc)) {
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
    } else {
        std::cout << "Error while getting the Nothing function\n";
        PyErr_Print();
    }
    Py_XDECREF(nothingFunc);
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
            }
            Py_XDECREF(key);
            Py_XDECREF(value);
            Py_DECREF(playerStatDict);
        } else {
            std::cout << "Error while getting the PlayerData function\n";
            PyErr_Print();
        }
    } else {
        std::cout << "Error while getting the PlayerData attribute\n";
        PyErr_Print();
    }
    Py_XDECREF(playerStatFunc);
}
