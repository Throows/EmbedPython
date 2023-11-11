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
   PyObject *func;
   PyObject *setIntArgs, *value;
   int result;

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

   SetMyInt(10);

   func = PyObject_GetAttrString(scriptModule, "getMyInt");
   if (func && PyCallable_Check(func)) {
      value = PyObject_CallObject(func, NULL);
      if (value != nullptr) {
         result = PyLong_AsLong(value);
         std::cout << "My int is : " << result << std::endl;
         Py_DECREF(value);
      } else {
         std::cout << "Error while calling the function" << std::endl;
         PyErr_Print();
      }
   } else {
      std::cout << "Error while getting the function" << std::endl;
      PyErr_Print();
   }
   Py_XDECREF(func);

   PyObject *funcT = PyObject_GetAttrString(scriptModule, "setMyInt");
   if (funcT && PyCallable_Check(funcT)) {
      setIntArgs = PyTuple_New(1);
      PyTuple_SetItem(setIntArgs, 0, PyLong_FromLong(2));
      value = PyObject_CallObject(funcT, setIntArgs);
      if (value != nullptr) {
         result = PyLong_AsLong(value);
         std::cout << "My new int is : " << result << std::endl;
         Py_DECREF(value);
      } else {
         std::cout << "Error while calling the function" << std::endl;
         PyErr_Print();
      }
      Py_XDECREF(setIntArgs);
   } else {
      std::cout << "Error while getting the function" << std::endl;
      PyErr_Print();
   }
   Py_XDECREF(funcT);

   std::cout << "Finaly my int is : " << GetMyInt() << std::endl;

   Py_XDECREF(gameModule);
   Py_XDECREF(scriptModule);

   return Py_FinalizeEx();
}