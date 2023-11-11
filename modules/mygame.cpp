#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#define MYGAME_MODULE
#include "mygame.hpp"

#define VERSION "0.0.1"

int MyNumber = 5;

void SetMyInt(int num)
{
    MyNumber = num;
}

int GetMyInt() 
{
    return MyNumber;
}

static PyObject* mygame_version(PyObject* self, PyObject* args) {
    return Py_BuildValue("s", VERSION);
}

static PyObject *mygame_getMyInt(PyObject *self, PyObject *args)
{
    return PyLong_FromLong(MyNumber);
}

static PyObject *mygame_setMyInt(PyObject *self, PyObject *args)
{
    int num;
    if (!PyArg_ParseTuple(args, "i", &num))
        return NULL;
    SetMyInt(num);
    return PyLong_FromLong(MyNumber);
}

static PyObject *mygame_GetRandomInt(PyObject *self, PyObject *args)
{
    int number = rand() % 100;
    return PyLong_FromLong(number);
}

static PyMethodDef mygame_methods[] = {
    {"version", mygame_version, METH_VARARGS, "Return some infos."},
    {"getMyInt", mygame_getMyInt, METH_VARARGS, "Return myInt."},
    {"setMyInt", mygame_setMyInt, METH_VARARGS, "Set and return myInt."},
    {"GetRandomInt", mygame_GetRandomInt, METH_VARARGS, "Get a random Int."},
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
    PyGame_API[0] = (void *)SetMyInt;
    PyGame_API[1] = (void *)GetMyInt;

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