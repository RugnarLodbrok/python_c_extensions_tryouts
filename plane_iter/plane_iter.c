#define PY_SSIZE_T_CLEAN
#include <Python.h>

typedef struct {
    PyObject_HEAD
    Py_ssize_t i;
    Py_ssize_t j;
    Py_ssize_t* x;
    Py_ssize_t* y;
    Py_ssize_t r;
    int first;
} IterState;

static PyObject* plane_iter_new(PyTypeObject* type, PyObject* args, PyObject* kwargs)
{
    IterState* self;

    if (!(self = (IterState*)type->tp_alloc(type, 0)))
        return NULL;

    self->r = 0;
    self->i = 0;
    self->j = 0;
    self->x = &(self->i);
    self->y = &(self->j);
    self->first = 1;

    return (PyObject*)self;
}

static void plane_iter_dealloc(IterState *self)
{
    Py_TYPE(self)->tp_free(self); // is it needed?
}

void swap(Py_ssize_t** a, Py_ssize_t** b)
{
    Py_ssize_t* c;

    c = *a;
    *a = *b;
    *b = c;
}

static PyObject* plane_iter_next(IterState* self)
{
    if (self->first)
    {
        self->first = 0;
        return Py_BuildValue("ii", 0, 0);
    }
    if (*(self->x) < self->r)
        (*(self->x))++;
    else if (*(self->y))
        (*(self->y))--;
    else
    {
        self->r++;
        (*(self->x))++;
        swap(&(self->x), &(self->y));
    }
    return Py_BuildValue("ii", self->i, self->j);
}



PyTypeObject PyPlaneIter_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    //PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "plane_iter",               /* tp_name */
    sizeof(IterState),              /* tp_basicsize */
    0,                              /* tp_itemsize */
    (destructor)plane_iter_dealloc,     /* tp_dealloc */
    0,                              /* tp_print */
    0,                              /* tp_getattr */
    0,                              /* tp_setattr */
    0,                              /* tp_reserved */
    0,                              /* tp_repr */
    0,                              /* tp_as_number */
    0,                              /* tp_as_sequence */
    0,                              /* tp_as_mapping */
    0,                              /* tp_hash */
    0,                              /* tp_call */
    0,                              /* tp_str */
    0,                              /* tp_getattro */
    0,                              /* tp_setattro */
    0,                              /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,             /* tp_flags */
    0,                              /* tp_doc */
    0,                              /* tp_traverse */
    0,                              /* tp_clear */
    0,                              /* tp_richcompare */
    0,                              /* tp_weaklistoffset */
    PyObject_SelfIter,              /* tp_iter */
    (iternextfunc)plane_iter_next,      /* tp_iternext */
    0,                              /* tp_methods */
    0,                              /* tp_members */
    0,                              /* tp_getset */
    0,                              /* tp_base */
    0,                              /* tp_dict */
    0,                              /* tp_descr_get */
    0,                              /* tp_descr_set */
    0,                              /* tp_dictoffset */
    0,                              /* tp_init */
    PyType_GenericAlloc,            /* tp_alloc */
    plane_iter_new,                     /* tp_new */
};

static struct PyModuleDef plane_iter_module = {
   PyModuleDef_HEAD_INIT,
   "plane_iter",                  /* m_name */
   "",                      /* m_doc */
   -1,                      /* m_size */
};

PyMODINIT_FUNC PyInit_plane_iter(void)
{
    PyObject* module;
    if (!(module = PyModule_Create(&plane_iter_module)))
        return NULL;

    if (PyType_Ready(&PyPlaneIter_Type) < 0)
        return NULL;
    Py_INCREF((PyObject *)&PyPlaneIter_Type);
    PyModule_AddObject(module, "plane_iter", (PyObject *)&PyPlaneIter_Type);

    return module;
}
