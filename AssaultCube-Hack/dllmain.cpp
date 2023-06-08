// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include "offset.h"

FILE* f = nullptr;
HANDLE hConsole = nullptr;

namespace GameAddress {
    DWORD baseModuleAddr;
    pLocalPlayer* localPlayerPtr;
}

namespace CheatState {
    bool isFreezeHealth = false;
    bool isFreezeArmor = false;
    bool isFreezeAmmo = false;
    bool isFreezeNades = false;
}

void OnExit(HMODULE hModule);
void KeyCheck();
void CheatCheck();
void PrintConsoleStatus();

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
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Main(HMODULE hModule) {
    std::cout << "Cheat injected\n";
    GameAddress::baseModuleAddr =  (DWORD)GetModuleHandle(nullptr);
    std::cout << "Game Address found at: " << GameAddress::baseModuleAddr << "\n";
    GameAddress::localPlayerPtr = GetLocalPlayer();
    std::cout << "Local Player Address found at: " << GameAddress::localPlayerPtr << "\n";

    PrintConsoleStatus();

    while (!GetAsyncKeyState(VK_END)) { // press End to unload dll
        KeyCheck();
        CheatCheck();
    }

    OnExit(hModule);
}

void KeyCheck() {
    bool isAnyToggle = false;
    if (GetAsyncKeyState(VK_F1) & 1) {
        isAnyToggle = true;
        CheatState::isFreezeHealth = !CheatState::isFreezeHealth;
    }
    if (GetAsyncKeyState(VK_F2) & 1) {
        isAnyToggle = true;
        CheatState::isFreezeArmor = !CheatState::isFreezeArmor;
    }
    if (GetAsyncKeyState(VK_F3) & 1) {
        isAnyToggle = true;
        CheatState::isFreezeAmmo = !CheatState::isFreezeAmmo;
    }
    if (GetAsyncKeyState(VK_F4) & 1) {
        isAnyToggle = true;
        CheatState::isFreezeNades = !CheatState::isFreezeNades;
    }
    
    if (isAnyToggle) {
        PrintConsoleStatus();
    }
}

void CheatCheck() {
    if (CheatState::isFreezeHealth) {
        GameAddress::localPlayerPtr->health = 100;
    }
    if (CheatState::isFreezeArmor) {
        GameAddress::localPlayerPtr->armor = 100;
    }
    if (CheatState::isFreezeAmmo) {
        GameAddress::localPlayerPtr->rifleAmmo = 20;
        GameAddress::localPlayerPtr->pistolAmmo = 12;
        GameAddress::localPlayerPtr->dualPistolAmmo = 20;
    }
    // turn this on after you get a nades to avoid conflict
    if (CheatState::isFreezeNades) {
        GameAddress::localPlayerPtr->nadesCount = 1;
    }
}

void PrintConsoleStatus() {
    COORD  pos = { 0,3 };
    SetConsoleCursorPosition(hConsole, pos);

    std::cout << "=================== STATUS ===================\n";
    std::cout << "F1 - Freeze Health: " << (CheatState::isFreezeHealth ? "ON\t" : "OFF\t") << std::endl;
    std::cout << "F2 - Freeze Armor: " << (CheatState::isFreezeArmor ? "ON\t" : "OFF\t") << std::endl;
    std::cout << "F3 - Freeze Ammo: " << (CheatState::isFreezeAmmo ? "ON\t" : "OFF\t") << std::endl;
    std::cout << "F4 - Freeze Nades: " << (CheatState::isFreezeNades ? "ON\t" : "OFF\t") << std::endl;
}

void OnExit(HMODULE hModule) {
    //clean up
    if (f) {
        fclose(f);
    }
    if (hConsole) {
        CloseHandle(hConsole);
    }
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
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
        CreateConsole();
        if (const HANDLE handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, 0))
        {
            CloseHandle(handle);
        }
        DisableThreadLibraryCalls(hModule);
        break;
    case DLL_THREAD_DETACH:
        OnExit(hModule);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

