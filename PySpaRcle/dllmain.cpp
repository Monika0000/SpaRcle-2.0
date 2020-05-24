// dllmain.cpp : Определяет точку входа для приложения DLL.

/*
    SpaRcle - Искра
    ИскРа = Искусственный Разум
*/

#include "pch.h"
#include "PythonHelper.h"
#include "SpaRcle.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        SpaRcle::Helper::Debug::InitColorTherme();
        SpaRcle::Helper::Debug::Library("SpaRcle dll process has been attached!");
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        SpaRcle::Helper::Debug::Library("SpaRcle dll process has been detached!");
        break;
    }
    return TRUE;
}

/*
class fooClass {
public:
    fooClass()  { };
    ~fooClass() { };
};




void fooInit(PyObject*) {

}
void fooDoSomething(PyObject*) {

}

static struct PyMethodDef foo_Methods[] = {
    { "__init__", (PyCFunction)fooInit, METH_VARARGS, "doc" },
    { "do_something", (PyCFunction)fooDoSomething, METH_VARARGS, "doc" },
    { 0, 0 },
};
*/

/*
void SomeMethod(PyObject*) { std::cout << "Call some method..." << std::endl; }
static struct PyMethodDef SpaRcleMethods[] = {
    { "SomeMethod", (PyCFunction)SomeMethod, METH_O, nullptr },
    { nullptr, nullptr, 0, nullptr }
}; 
*/

static struct PyModuleDef cModPySpaRcle = {
    PyModuleDef_HEAD_INIT,
    "sparcle",
    "",
    -1, // -1 or 0
    NULL, NULL, NULL, NULL, NULL //SpaRcleMethods
};

PyMODINIT_FUNC PyInit_PySpaRcle() {
    SpaRcle::Helper::Debug::Library("Initializing PySpaRcle dll...");
    //Py_Initialize();

    //!----------------------------------------------------------------------------
    //!PyObject* fooClass = PythonHelper::createClassObject("fooClass", foo_Methods);
    //!PyModule_AddObject(module, "foo", fooClass);

    PyObject* module;

    sparcle_SpaRcleType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&sparcle_SpaRcleType) < 0)
        return NULL;

    module = PyModule_Create(&cModPySpaRcle);
    if (module == NULL)
        return NULL;

    Py_INCREF(&sparcle_SpaRcleType);
    PyModule_AddObject(module, "SpaRcle", (PyObject*)&sparcle_SpaRcleType);

    //PyObject* obj = new PyObject();
    //Py_Initialize();
    //PyImport_AddModule()

    //!----------------------------------------------------------------------------

    SpaRcle::Helper::Debug::Library("Initializing PySpaRcle dll completed!");
    return module;
}