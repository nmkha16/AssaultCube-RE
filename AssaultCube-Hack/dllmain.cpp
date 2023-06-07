// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include "offset.h"

FILE* f = nullptr;

namespace GameAddress {
    DWORD baseModuleAddr;
    pLocalPlayer* localPlayerPtr;
}

pLocalPlayer* GetLocalPlayer()
{
    auto localPlayer = (pLocalPlayer*) (*(DWORD*)(GameAddress::baseModuleAddr + Offset::localPlayerOffset));

    if (localPlayer == NULL) return NULL;

    return localPlayer;
}

void CreateConsole() {
    AllocConsole();
    //FILE* f = nullptr;
    freopen_s(&f, "CONOUT$", "w", stdout);
}

void Main(HMODULE hModule) {
    CreateConsole();
    std::cout << "Cheat injected\n";
    GameAddress::baseModuleAddr =  (DWORD)GetModuleHandle(nullptr);
    std::cout << "Game Address: " << GameAddress::baseModuleAddr << "\n";
    GameAddress::localPlayerPtr = GetLocalPlayer();
    std::cout << "Local Player Address: " << GameAddress::localPlayerPtr << "\n";

    // testing cheat
    while (true) {
        std::cout << GameAddress::localPlayerPtr->rifleAmmo << std::endl;
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        if (const HANDLE handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, 0))
        {
            CloseHandle(handle);
        }
        DisableThreadLibraryCalls(hModule);
        break;
    case DLL_THREAD_DETACH:
        //clean up
        if (f) {
            fclose(f);
        }
        FreeConsole();
        FreeLibraryAndExitThread(hModule, 0);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

