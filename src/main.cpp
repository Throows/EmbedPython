/* ----------------------------------------------------------------------- */
// Author  :  Romain Berthoule
// Date    :  22/10/2023
// Project :  EmbedPython
// File    :  main.cpp (clang14.0.3)
// Desc    :  This is the entry point file 
/* ----------------------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <filesystem>
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "mygame.hpp"

int main(int argc, char **argv)
{
   std::filesystem::path exePath = argv[0];
   std::filesystem::current_path(exePath.parent_path());

   std::cout << "------ EmbedPython ------" << std::endl;

   PyObject *gameModule, *scriptModule;
   PyObject *func, *operObj;
   PyObject *value, *resValue;
   PyObject *operArgs;

   Py_Initialize();
   PyRun_SimpleString("import os");
   PyRun_SimpleString("import sys");
   std::string cmdRun = "sys.path.append(\"" + std::filesystem::current_path().native() + "/scripts\")";
   PyRun_SimpleString(cmdRun.c_str());

   gameModule = PyImport_ImportModule("mygame");
   if (gameModule == nullptr) {
      std::cout << "Error while importing the Game module\n";
      PyErr_Print();
      return 0;
   }

   if (import_mygame() < 0) {
      printf("Error importing mygame module\n");
      return 0;
   }

   scriptModule = PyImport_ImportModule("MyScript");
   if (scriptModule == nullptr) {
      std::cout << "Error while importing the Scripting module\n";
      PyErr_Print();
      return 0;
   }

   // Game Info Module
   func = PyObject_GetAttrString(gameModule, "version");
   if (func && PyCallable_Check(func)) {
      value = PyObject_CallObject(func, NULL);
      if (value != nullptr) {
         std::cout << "Game Version : " << PyUnicode_AsUTF8(value) << std::endl;
         Py_DECREF(value);
      } else {
         std::cout << "Error while calling the function" << std::endl;
         PyErr_Print();
      }
   }
   Py_XDECREF(func);

   PyObject *gameData = PyObject_GetAttrString(scriptModule, "data");
   if (gameData && PyDict_Check(gameData)) {
      PyObject *key, *value;
      Py_ssize_t pos = 0;

      while (PyDict_Next(gameData, &pos, &key, &value)) {
         std::cout << PyUnicode_AsUTF8(key) << " : ";
         if (PyLong_Check(value)) {
            std::cout << PyLong_AsLong(value) << std::endl;
         } else {
            std::cout << PyUnicode_AsUTF8(value) << std::endl;
         }
      }
      Py_XDECREF(key);
      Py_XDECREF(value);
   }
   Py_XDECREF(gameData);

   operObj = PyObject_GetAttrString(scriptModule, "Operation");
   if (operObj && PyCallable_Check(operObj)) {
      operArgs = PyTuple_New(2);
      PyTuple_SetItem(operArgs, 0, PyLong_FromLong(2));
      PyTuple_SetItem(operArgs, 1, PyLong_FromLong(3));
      value = PyObject_CallObject(operObj, operArgs);
      if (value != nullptr) {
         func = PyUnicode_DecodeFSDefault("GetResult");
         if (func != nullptr) {
            resValue = PyObject_CallMethodObjArgs(value, func, NULL);
            if (resValue != nullptr) {
               int result = PyLong_AsLong(resValue);
               std::cout << "The result is : " << result << std::endl;
               Py_DECREF(resValue);
            }
            Py_DECREF(func);
         }
         Py_DECREF(value);
      } else {
         std::cout << "Error while calling the function" << std::endl;
         PyErr_Print();
      }
      Py_DECREF(operArgs);
      Py_DECREF(operObj);
   } else {
      std::cout << "Error while getting the function" << std::endl;
      PyErr_Print();
   }

   Py_DECREF(gameModule);
   Py_DECREF(scriptModule);

   return Py_FinalizeEx();
}