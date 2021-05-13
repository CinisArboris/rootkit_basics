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
        system("mkdir C:\\DLL_PROCESS_ATTACH");
        system("whoami > C:\\DLL_PROCESS_ATTACH\\info");
        break;
    case DLL_THREAD_ATTACH:
        system("mkdir C:\\DLL_THREAD_ATTACH");
        system("whoami > C:\\DLL_THREAD_ATTACH\\info");
        loaded = true;
        break;
    case DLL_THREAD_DETACH:
        system("mkdir C:\\DLL_THREAD_DETACH");
        system("whoami > C:\\DLL_THREAD_DETACH\\info");
        loaded = true;
        break;
    case DLL_PROCESS_DETACH:
        system("mkdir C:\\DLL_PROCESS_DETACH");
        system("whoami > C:\\DLL_PROCESS_DETACH\\info");
        loaded = true;
        break;
    }
    return TRUE;
}

extern "C" __declspec (dllexport) bool example() {
    return loaded;
}

