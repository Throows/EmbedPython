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

void PythonPlayer::CreatePlayer(Player *player, const char *scriptName)
{
    PyObject *playerModule, *gameData;
    playerModule = PyImport_ImportModule(scriptName);
    if (playerModule == nullptr) {
        std::cout << "Error while importing the " << scriptName << " module\n";
        PyErr_Print();
        return;
    }

    gameData = PyObject_GetAttrString(playerModule, "PlayerData");
    if (gameData && PyDict_Check(gameData)) {
        PyObject *key, *value;
        Py_ssize_t pos = 0;

        while (PyDict_Next(gameData, &pos, &key, &value)) {
            std::string keyStr = PyUnicode_AsUTF8(key);
            if (keyStr == "Name")           player->SetName(PyUnicode_AsUTF8(value));
            else if (keyStr == "Health")    player->SetHealth(PyLong_AsLong(value));
            else if (keyStr == "Damage")    player->SetDamage(PyLong_AsLong(value));
            else if (keyStr == "Armor")     player->SetArmor(PyLong_AsLong(value));
            else if (keyStr == "Speed")     player->SetSpeed(PyLong_AsLong(value));
            else if (keyStr == "Level")     player->SetLevel(PyLong_AsLong(value));
            else if (keyStr == "Experience") player->SetExperience(PyLong_AsLong(value));
            else std::cout << "Error while getting the " << keyStr << " attribute\n";
        }
        Py_XDECREF(key);
        Py_XDECREF(value);
        Py_DECREF(gameData);
    } else {
        std::cout << "Error while getting the PlayerData attribute\n";
        PyErr_Print();
    }
    Py_DECREF(playerModule);

    return;
}

Action PythonPlayer::ChoseAction(Player *player, const char *scriptName)
{
    Action action = Action::ERROR;
    PyObject *playerModule, *playerObject, *actionFunc;
    PyObject *playerObjectValue, *actionResult;
    playerModule = PyImport_ImportModule(scriptName);
    if (playerModule == nullptr) {
        std::cout << "Error while importing the " << scriptName << " module\n";
        return action;
    }

    playerObject = PyObject_GetAttrString(playerModule, "Player");
    if (playerObject == nullptr || !PyCallable_Check(playerObject)) {
        std::cout << "Error while getting the Player attribute\n";
        PyErr_Print();
        goto noPlayerObj;
    }

    playerObjectValue = PyObject_CallObject(playerObject, NULL);
    if (playerObjectValue == nullptr) {
        std::cout << "Error while calling the Player object\n";
        PyErr_Print();
        goto noPlayerObj;
    }

    actionFunc = PyUnicode_DecodeFSDefault("ChoseAction");
    if (actionFunc != nullptr) {
        actionResult = PyObject_CallMethodObjArgs(playerObjectValue, actionFunc, NULL);
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

    Py_DECREF(playerObjectValue);
noPlayerObj:
    Py_DECREF(playerObject);
noPlayerObjAttr:
    Py_DECREF(playerModule);
    return action;
}
