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

   PyObject *name, *objModule, *func;
   PyObject /**objArgs,*/ *value;
   int result;

   Py_Initialize();
   PyRun_SimpleString("import os");
   PyRun_SimpleString("import sys");
   PyRun_SimpleString("sys.path.append(os.getcwd() + \"/scripts\")");
   PyRun_SimpleString("import mygame");
   name = PyUnicode_DecodeFSDefault("MyScript"); // MyScript is the name of the py file
   objModule = PyImport_Import(name);
   Py_DECREF(name);

   if (import_mygame() < 0) {
      printf("Error importing mygame module\n");
      return 0;
   }

   PyRun_SimpleString("mygame.infos()");
   SetMyInt(10);

   if (objModule != nullptr) {
      func = PyObject_GetAttrString(objModule, "getMyInt");

      if (func && PyCallable_Check(func)) {
         //objArgs = PyTuple_New(1);
         //PyTuple_SetItem(objArgs, 0, PyLong_FromLong(2));
         value = PyObject_CallObject(func, NULL); // objArgs
         if (value != nullptr) {
            result = PyLong_AsLong(value);
            std::cout << "My int is : " << result << std::endl;
            Py_DECREF(value);
         }
         else {
            std::cout << "Error while calling the function" << std::endl;
            PyErr_Print();
         }
      } else {
         std::cout << "Error while getting the function" << std::endl;
         PyErr_Print();
      }
      Py_XDECREF(func);
   } else {
      std::cout << "Error while importing the module" << std::endl;
      PyErr_Print();
   }
   Py_XDECREF(objModule);

   return Py_FinalizeEx();
}