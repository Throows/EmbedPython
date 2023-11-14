#include <string>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#define MYGAME_MODULE
#include "mygame.hpp"

#define VERSION "0.0.1"

static PyObject* mygame_version(PyObject* self, PyObject* args)
{
    return Py_BuildValue("s", VERSION);
}

static PyObject *mygame_GetRandomInt(PyObject *self, PyObject *args)
{
    int number = rand() % 4;
    return PyLong_FromLong(number);
}

static PyObject* mygame_Say(PyObject* self, PyObject* args)
{
    const char* text;
    if (!PyArg_ParseTuple(args, "s", &text))
        return NULL;
        
    std::cout << appInstance->GetPlayingPlayerName() << " -> " << text << std::endl;
    Py_RETURN_NONE;
}

static PyMethodDef mygame_methods[] = {
    {"version", mygame_version, METH_VARARGS, "Return some infos."},
    {"GetRandomInt", mygame_GetRandomInt, METH_VARARGS, "Get a random Int."},
    {"Say", mygame_Say, METH_VARARGS, "Say something"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef mygame_module = {
    PyModuleDef_HEAD_INIT,
    "mygame",
    "My Game Module",
    -1,
    mygame_methods
};

PyMODINIT_FUNC PyInit_mygame(void)
{
    PyObject *m;
    static void *PyGame_API[FUNC_NB];
    PyObject *c_api_object;

    m = PyModule_Create(&mygame_module);
    if (m == NULL)
        return NULL;

    /* Initialize the C API pointer array */
    //PyGame_API[0] = (void *);

    /* Create a Capsule containing the API pointer array's address */
    c_api_object = PyCapsule_New((void *)PyGame_API, "mygame._C_API", NULL);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return NULL;
    }

    srand((unsigned)time(NULL));

    return m;
}

#ifdef __cplusplus
}
#endif