#include "PyInterpreter.hpp"
#include <iostream>
#include "mygame.hpp"

PyInterpreter::PyInterpreter(const char *scriptPath) : m_scriptsPath(scriptPath)
{
}

PyInterpreter::~PyInterpreter()
{
}

void PyInterpreter::Initialize()
{
    if (!isInitialized) {
        PyObject *sysModule, *path;
        Py_Initialize();

        sysModule = PyImport_ImportModule("sys");
        if (sysModule == nullptr) {
            std::cout << "Error while importing the SYS module\n";
            PyErr_Print();
            return;
        }

        path = PyObject_GetAttrString(sysModule, "path");
        if (path == nullptr) {
            std::cout << "Error while getting the PATH attribute\n";
            PyErr_Print();
            Py_DECREF(sysModule);
            return;
        }
        PyList_Append(path, PyUnicode_FromString(m_scriptsPath));

        Py_DECREF(sysModule);
        Py_DECREF(path);

        PyObject *gmodule = PyImport_ImportModule("mygame");
        Py_INCREF(gmodule);
        this->m_gameModule = gmodule;
        if (this->m_gameModule != nullptr) {
            if(import_mygame() < 0) {
                printf("Error importing mygame module\n");
                return;
            }
        } else {
            std::cout << "Error while importing the mygame module\n";
            PyErr_Print();
            return;
        }
        this->isInitialized = true;
    }
}

void PyInterpreter::Uninitialize()
{
    Py_CLEAR(this->m_gameModule);
    Py_FinalizeEx();
}
