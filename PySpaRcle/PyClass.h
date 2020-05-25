#pragma once
#include <SRHelper.h>
#include <boost/python.hpp>
#include <string>
#include <vector>

struct IPyClass {
    PyObject_HEAD
    static PyObject* name(IPyClass* self) { return PyUnicode_FromString("<SpaRcle.Debug>"); }
protected:
    /*
    virtual void      Deadloc(IPyClass* self) = 0;
    virtual IPyClass* New(IPyClass* self, 
                          PyTypeObject* type, 
                          PyObject* args, 
                          PyObject* kwds)                                  = 0;
    virtual int       Init(IPyClass* self, PyObject* args, PyObject* kwds) = 0;
    */
private:
    static void _dealloc(IPyClass* self);
    static PyObject* _new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
        IPyClass* self;

        self = (IPyClass*)type->tp_alloc(type, 0);
       // if (self) {
        //    self = self->New(self, type, args, kwds);
        //}
        return (PyObject*)self;
    }
    static int _init(IPyClass* self, PyObject* args, PyObject* kwds);
public:
    PyObject* _class;
public:
    std::string class_name;
    std::string type_name;
    std::string doc;
    Py_ssize_t size;
    IPyClass(std::string class_name, std::string type_name, std::string doc, Py_ssize_t size) :
        class_name(class_name), type_name(type_name), doc(doc), size(size)
    {

    }
public:
    virtual PyMethodDef* GetMethods() = 0;
    PyTypeObject* GetType();
};

int IPyClass::_init(IPyClass* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = { NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|SSi", kwlist))
        return -1;


    return 0;// self->Init(self, args, kwds);
}
void IPyClass::_dealloc(IPyClass* self) {
    self->class_name.~basic_string();
    self->doc.~basic_string();
    self->type_name.~basic_string();
    Py_TYPE(self)->tp_free((PyObject*)self);
}
PyTypeObject* IPyClass::GetType() {
    static PyTypeObject* type = new PyTypeObject{
        PyVarObject_HEAD_INIT(NULL, 0)
        type_name.c_str(),           // tp_name//
        size,             // tp_basicsize//
        0,                         // tp_itemsize//
        (destructor)_dealloc, // tp_dealloc//
        0,                         // tp_print//
        0,                         // tp_getattr//
        0,                         // tp_setattr//
        0,                         // tp_reserved//
        0,                         // tp_repr//
        0,                         // tp_as_number//
        0,                         // tp_as_sequence//
        0,                         // tp_as_mapping//
        0,                         // tp_hash //
        0,                         // tp_call//
        0,                         // tp_str//
        0,                         // tp_getattro//
        0,                         // tp_setattro//
        0,                         // tp_as_buffer//
        Py_TPFLAGS_DEFAULT |
            Py_TPFLAGS_BASETYPE,   // tp_flags//
        doc.c_str(),           // tp_doc//
        0,                         // tp_traverse//
        0,                         // tp_clear//
        0,                         // tp_richcompare//
        0,                         // tp_weaklistoffset//
        0,                         // tp_iter//
        0,                         // tp_iternext//
        GetMethods(),                    // tp_methods//
        0,//Noddy_members,             // tp_members//
        0,//Noddy_getseters,           // tp_getset//
        0,                         // tp_base//
        0,                         // tp_dict//
        0,                         // tp_descr_get//
        0,                         // tp_descr_set//
        0,                         // tp_dictoffset//
        (initproc)IPyClass::_init,      // tp_init//
        0,                         // tp_alloc//
        IPyClass::_new,                 // tp_new//
    };
    return type;
};