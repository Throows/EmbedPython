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
        Py_Initialize();
        PyObject *osModule = PyImport_ImportModule("os");
        if (osModule == nullptr) {
            std::cout << "Error while importing the OS module\n";
            PyErr_Print();
            return;
        }
        PyObject *sysModule = PyImport_ImportModule("sys");
        if (sysModule == nullptr) {
            std::cout << "Error while importing the SYS module\n";
            PyErr_Print();
            return;
        }
        PyObject *path = PyObject_GetAttrString(sysModule, "path");
        if (path == nullptr) {
            std::cout << "Error while getting the PATH attribute\n";
            PyErr_Print();
            return;
        }
        PyList_Append(path, PyUnicode_FromString(m_scriptsPath));

        Py_DECREF(osModule);
        Py_DECREF(sysModule);
        Py_DECREF(path);

        this->LoadCModule(this->m_gameModule, "mygame");

        this->isInitialized = true;
    }
}

void PyInterpreter::Uninitialize()
{
    if (this->m_gameModule != nullptr)
        Py_DECREF(this->m_gameModule);

    Py_FinalizeEx();
}



void PyInterpreter::LoadCModule(PyObject *module, const char *moduleName)
{   
    this->LoadScriptModule(module, moduleName);
    
    if (moduleName == "mygame" && import_mygame() < 0) {
        printf("Error importing mygame module\n");
        return;
    }
}

void PyInterpreter::LoadScriptModule(PyObject *module, const char *moduleName)
{
    module = PyImport_ImportModule(moduleName);
    if (module == nullptr) {
        std::cout << "Error while importing the " << moduleName << " module\n";
        PyErr_Print();
        return;
    }
}
