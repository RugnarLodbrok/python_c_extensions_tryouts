#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *exmodError;

static PyObject* exmod_say_hello(PyObject* self, PyObject* args)
{
    const char* msg;
    int sts = 0;
    if (!PyArg_ParseTuple(args, "s", &msg))
        return NULL;
    if (!strcmp(msg, "ERROR"))
    {
        PyErr_SetString(exmodError, "ERR VAL");
        return NULL;
    }
    printf("HELLO C FROM PY!\n message: `%s`\n", msg);
    sts = 21;
    return Py_BuildValue("i", sts);
}

static PyObject* exmod_add(PyObject* self, PyObject* args)
{
    double a;
    double b;
    double sts;

    if (!PyArg_ParseTuple(args, "dd", &a, &b))
        return NULL;

    sts = a + b;
    printf("HELLO C FROM PY!\n %f + %f = %f\n", a, b, sts);
    return Py_BuildValue("i", sts);
}

static PyMethodDef exmod_methods[] = {
    {"say_hello", exmod_say_hello, METH_VARARGS, "say hello doc"},
    {"add", exmod_add, METH_VARARGS, "exmod add doc"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef exmod_definition = {
    PyModuleDef_HEAD_INIT,
    "exmod",
    "A Python module that prints 'hello world' from C code.",
    -1,
    exmod_methods
};

PyMODINIT_FUNC PyInit_exmod(void)
{
    Py_Initialize();
    return PyModule_Create(&exmod_definition);
}
