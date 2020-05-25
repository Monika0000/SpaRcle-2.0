// dllmain.cpp : Определяет точку входа для приложения DLL.
/*
    SpaRcle - Искра
    ИскРа = Искусственный Разум
*/

#include "pch.h"
#include "SpaRcle.h"
#include "PyDebug.h"
PyObject* module;

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

//static PyObject* getname(IPyClass* self) { return PyUnicode_FromString("<SpaRcle.Debug>"); }


//PyMethodDef Debug_methods[] = {
 //   {"name", (PyCFunction)PyDebug::name, METH_NOARGS, "Return the name, combining the first and last name" },
 //   {NULL}  // Sentinel 
//};
/*
PyTypeObject* GetType() {
    PyDebug* debug = new PyDebug();

    PyTypeObject* type = new PyTypeObject{
        PyVarObject_HEAD_INIT(NULL, 0)
        "sparcle.Debug",           // tp_name//
        sizeof(PyDebug),             // tp_basicsize//
        0,                         // tp_itemsize//
        (destructor)PyDebug::_dealloc, // tp_dealloc//
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
        "Debug objects",           // tp_doc//
        0,                         // tp_traverse//
        0,                         // tp_clear//
        0,                         // tp_richcompare//
        0,                         // tp_weaklistoffset//
        0,                         // tp_iter//
        0,                         // tp_iternext//
        debug->GetMethods(),                    // tp_methods//
        0,//Noddy_members,             // tp_members//
        0,//Noddy_getseters,           // tp_getset//
        0,                         // tp_base//
        0,                         // tp_dict//
        0,                         // tp_descr_get//
        0,                         // tp_descr_set//
        0,                         // tp_dictoffset//
        (initproc)PyDebug::_init,      // tp_init//
        0,                         // tp_alloc//
        PyDebug::_new,                 // tp_new//
    };
    return type;
}
*/

void M(){
    std::cout << 324 << std::endl;
};

PyMODINIT_FUNC PyInit_PySpaRcle() {
    SpaRcle::Helper::Debug::Library("Initializing PySpaRcle dll...");
    //Py_Initialize();

    //!----------------------------------------------------------------------------
    //!PyObject* fooClass = PythonHelper::createClassObject("fooClass", foo_Methods);
    //!PyModule_AddObject(module, "foo", fooClass);

    //!sparcle_SpaRcleType.tp_new = PyType_GenericNew;
    //!if (PyType_Ready(&sparcle_SpaRcleType) < 0)
    //!   return NULL;

    //if (PyType_Ready(&DebugType) < 0)
    //    return NULL;

    module = PyModule_Create(&cModPySpaRcle);
    if (module == NULL)
        return NULL;

    PyDebug* debug = new PyDebug("Debug", "sparcle.Debug", "SpaRcle debugger");
    RegisterPythonClass(debug, module);
    //PyTypeObject* type = debug->GetType();
    //PyType_Ready(type);
    //Py_INCREF(type);
    //PyModule_AddObject(module, debug->class_name.c_str(), (PyObject*)type);


    /*
    PyDebug* debug = new PyDebug("Debug", "sparcle.Debug", "SpaRcle debugger");
    //module = AddClass(debug, module);
    

    if (PyType_Ready(&debug->GetType()) < 0)
        return NULL;

    Py_INCREF(&debug->GetType());
    PyModule_AddObject(module, debug->class_name.c_str(), (PyObject*)&debug->GetType());
    */
    //!----------------------------------------------------------------------------

    SpaRcle::Helper::Debug::Library("Initializing PySpaRcle dll completed!");
    return module;
}