#include "skype_rc4.h"

#include <Python.h>


typedef struct {
    PyObject_HEAD
    RC4_context ctx;
} PyRC4_context;


static int
PyRC4_init(PyRC4_context *self, PyObject *args, PyObject *kwds)
{
	unsigned int iv;
	if (!PyArg_ParseTuple(args, "l", &iv))
		return NULL;

	Skype_RC4_Expand_IV(iv, NULL, &self->ctx, 1, 0);

	return 0;
}

static PyObject *
PyRC4_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyRC4_context *self;

    self = (PyRC4_context *)type->tp_alloc(type, 0);
    if (self == NULL)
        goto out;

out:
    return (PyObject *)self;

}

static PyObject * do_crypt(PyRC4_context* self, PyObject *data, int test) {

    char *c_data = PyString_AsString(data);
    int len = PyString_Size(data);
    RC4_crypt(c_data, len, &self->ctx, test);
    return PyString_FromStringAndSize(c_data, len);
}

static PyObject * PyRC4_crypt(PyRC4_context* self, PyObject *data) {
    return do_crypt(self, data, 0);
}

static PyObject * PyRC4_test(PyRC4_context* self, PyObject *data) {
    return do_crypt(self, data, 1);
}

static PyMethodDef PyRC4_methods[] = {
	{"crypt", (PyCFunction)PyRC4_crypt, METH_O,
        "crypt or decrypt object"},
	{"test", (PyCFunction)PyRC4_test, METH_O,
        "crypt or decrypt object (test mode)"},

   {NULL}  /* Sentinel */
};


static PyTypeObject PyRC4_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "epycs.rc4.PyRC4_context",             /*tp_name*/
    sizeof(PyRC4_context),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,//(destructor)RbusRoot_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "RC4 objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    PyRC4_methods,             /* tp_methods */
    0, //RbusRoot_members,             /* tp_members */
    0, //RbusRoot_getseters,           /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PyRC4_init,      /* tp_init */
    0,                         /* tp_alloc */
    PyRC4_new,                 /* tp_new */
};

static PyMethodDef module_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initrc4(void) 
{
    PyObject* m;

    if (PyType_Ready(&PyRC4_Type) < 0)
        return;

    m = Py_InitModule3("epycs.rc4", module_methods,
		    "Skepe RC4 bindings");

    if (m == NULL)
      return;

    Py_INCREF(&PyRC4_Type);
    PyModule_AddObject(m, "RC4", (PyObject *)&PyRC4_Type);
}
