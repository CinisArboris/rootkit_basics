// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include <process.h>
#include <iostream>
//fileapi.h
#include <fileapi.h>

using namespace std;

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved){
    switch (ul_reason_for_call){
    case DLL_PROCESS_ATTACH:
        system("mkdir C:\\DLL_PROCESS_ATTACH");
        CreateDirectory(L"C:\\DLL_PROCESS_DETACH", NULL);
        system("cmd.exe");
        break;
    case DLL_THREAD_ATTACH:
        system("mkdir C:\\DLL_THREAD_ATTACH");
        CreateDirectory(L"C:\\DLL_PROCESS_DETACH", NULL);
        system("cmd.exe");
        break;
    case DLL_THREAD_DETACH:
        system("mkdir C:\\DLL_THREAD_DETACH");
        CreateDirectory(L"C:\\DLL_PROCESS_DETACH", NULL);
        system("cmd.exe");
        break;
    case DLL_PROCESS_DETACH:
        system("mkdir C:\\DLL_PROCESS_DETACH");
        CreateDirectory(L"C:\\DLL_PROCESS_DETACH", NULL);
        system("cmd.exe");
        break;
    }
    system("mkdir C:\\hallo");
    CreateDirectory(L"C:\\DLL_PROCESS_DETACH", NULL);
    system("cmd.exe");
    return TRUE;
}

