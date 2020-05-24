#pragma once
#include <SRHelper.h>
#include <boost/python.hpp>
#include <boost/python/class.hpp>
#include <Python.h>

using namespace boost::python;

class PythonHelper {
public:
    static PyObject* createClassObject(const char* name, PyMethodDef methods[]) {
        printf("     add class %s\n", name);
        PyObject* pClassName = PyUnicode_FromString(name);
        PyObject* pClassBases = PyTuple_New(0); // An empty tuple for bases is equivalent to '(object,)'
        PyObject* pClassDic = PyDict_New();


        PyMethodDef* def;
        // add methods to class 
        for (def = methods; def->ml_name != NULL; def++)
        {
            printf("     add method %s\n", def->ml_name);
            PyObject* func = PyCFunction_New(def, NULL);
            PyObject* method = PyInstanceMethod_New(func);
            PyDict_SetItemString(pClassDic, def->ml_name, method);
            Py_DECREF(func);
            Py_DECREF(method);
        }

        // pClass = type(pClassName, pClassBases, pClassDic)
        PyObject* pClass = PyObject_CallFunctionObjArgs((PyObject*)&PyType_Type, pClassName, pClassBases, pClassDic, NULL);

        Py_DECREF(pClassName);
        Py_DECREF(pClassBases);
        Py_DECREF(pClassDic);


        return pClass;
    }
};
/*
PyObject* GetSomeClass(PyObject*) {
    PyObject* pClassName = PyBytes_FromString("MyClass");
    PyObject* pClassBases = PyTuple_New(0); // An empty tuple for bases is equivalent to `(object,)`
    PyObject* pClassDic = PyDict_New();

    // pClass = type(pClassName, pClassBases, pClassDic)
    PyObject* pClass = PyObject_CallFunctionObjArgs(pClassName, pClassBases, pClassDic, NULL);

    Py_CLEAR(pClassName);
    Py_CLEAR(pClassBases);
    Py_CLEAR(pClassDic);

    return pClass;
}*/
/*
BOOST_PYTHON_MODULE(PySpaRcle)
{
    class_<Some>("Some")

        ;
}
*/
//PyObject* SomeMethod(PyObject*) {
//    std::cout << "Call some method..." << std::endl;
//    return PyFloat_FromDouble(0.0); }