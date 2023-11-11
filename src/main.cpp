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
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "mygame.hpp"

int main(int argc, char **argv)
{
   std::cout << "------ EmbedPython ------" << std::endl;

   PyObject *gameModule, *scriptModule;
   PyObject *func, *operObj;
   PyObject *value, *resValue;

   Py_Initialize();
   PyRun_SimpleString("import os");
   PyRun_SimpleString("import sys");
   PyRun_SimpleString("sys.path.append(os.getcwd() + \"/scripts\")");

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

   operObj = PyObject_GetAttrString(scriptModule, "Operation");
   if (operObj && PyCallable_Check(operObj)) {
      /*setIntArgs = PyTuple_New(1);
      PyTuple_SetItem(setIntArgs, 0, PyLong_FromLong(2));*/
      value = PyObject_CallObject(operObj, NULL);
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
      Py_DECREF(operObj);
   } else {
      std::cout << "Error while getting the function" << std::endl;
      PyErr_Print();
   }

   Py_XDECREF(gameModule);
   Py_XDECREF(scriptModule);

   return Py_FinalizeEx();
}