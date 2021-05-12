// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include <process.h>
#include <iostream>
//fileapi.h
#include <fileapi.h>

using namespace std;

bool loaded = false;

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved){
    switch (ul_reason_for_call){
    case DLL_PROCESS_ATTACH:
        loaded = true;
        break;
    case DLL_THREAD_ATTACH:
        loaded = true;
        break;
    case DLL_THREAD_DETACH:
        loaded = true;
        break;
    case DLL_PROCESS_DETACH:
        loaded = true;
        break;
    }
    return TRUE;
}

extern "C" __declspec (dllexport) bool example() {
    return loaded;
}

