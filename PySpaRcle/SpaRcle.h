#pragma once
#include <SRHelper.h>
#include <boost/python.hpp>
#include "PyClass.h"

void RegisterPythonClass(IPyClass* pyclass, PyObject* module) {
    PyTypeObject* type = pyclass->GetType();
    PyType_Ready(type);
    Py_INCREF(type);
    PyModule_AddObject(module, pyclass->class_name.c_str() , (PyObject*)type);
}

typedef struct {
    PyObject_HEAD
        /* Type-specific fields go here. */
} SpaRcle_SpaRcleObject;
static PyTypeObject sparcle_SpaRcleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "sparcle.SpaRcle",             /* tp_name */
    sizeof(SpaRcle_SpaRcleObject), /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "SpaRcle objects",           /* tp_doc */
};
