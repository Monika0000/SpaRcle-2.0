#pragma once
#include "PyClass.h"

struct PyDebug : public IPyClass {
private:
    static int Init(IPyClass* self, PyObject* args, PyObject* kwds) {
        //PyObject* path = NULL;

        //char char_path[] = "path";
        static char* kwlist[] = { NULL };
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "|SSi", kwlist
            ///,&path
        ))
            return -1;

        //std::cout << (char*)path << std::endl;

        self->_class = (PyObject*)(new SpaRcle::Helper::Debug("J:\\C++\\SpaRcle\\x64\\Debug"));

        return 0;// self->Init(self, args, kwds);
    }
public:
    PyDebug(std::string class_name, std::string type_name, std::string doc):IPyClass(class_name, type_name, doc, sizeof(PyDebug)) {
        this->GetType()->tp_init = (initproc)Init;
    }
public:
    static PyObject* Log(IPyClass* self) { 
        SpaRcle::Helper::Debug* deb = (SpaRcle::Helper::Debug*)self->_class;
        deb->Log("Just Monika!");
        return PyUnicode_FromString("Console log. TODO IT!"); 
    }
public:
    PyMethodDef* GetMethods() override;
};


PyMethodDef PyDebug_methods[] = {
    {"name", (PyCFunction)PyDebug::name, METH_NOARGS, "Return the name" },
    {"Log",  (PyCFunction)PyDebug::Log,  METH_NOARGS, "Loging" },
    {NULL} 
};

PyMethodDef* PyDebug::GetMethods() { return PyDebug_methods; }


