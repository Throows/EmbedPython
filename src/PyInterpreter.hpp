#pragma once 
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>

class PyInterpreter
{

public:
    PyInterpreter(const char *scriptPath);
    ~PyInterpreter();

    void Initialize();
    void Uninitialize();

    void LoadCModule(PyObject *module, const char *moduleName);
    void LoadScriptModule(PyObject *module, const char *moduleName);

private:
    const char *m_scriptsPath;
    bool isInitialized = false;
    std::vector<PyObject*> m_loadedModules;
    PyObject* m_gameModule;
};
