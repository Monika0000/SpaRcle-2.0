// dllmain.cpp : Определяет точку входа для приложения DLL.

#include "pch.h"
#include <SRHelper.h>
#include <boost/python.hpp>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::cout << "SpaRcle has been attached!\n";
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

using namespace boost::python;

class Some {

};

BOOST_PYTHON_MODULE(example)
{
    class_<Some>("Some")

        ;
}

//PyMODINIT_FUNC PyInit_proj_module() {
//
//}