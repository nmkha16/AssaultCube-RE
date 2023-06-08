#pragma once
#include <iostream>

namespace Offset {
	DWORD localPlayerOffset = 0x109B74;
}

// Created with ReClass.NET 1.2 by KN4CK3R

class pLocalPlayer
{
public:
	char pad_0000[4]; //0x0000
	float x; //0x0004
	float y; //0x0008
	float z; //0x000C
	char pad_0010[48]; //0x0010
	float pitch; //0x0040
	float yaw; //0x0044
	float roll; //0x0048
	char pad_004C[172]; //0x004C
	int32_t health; //0x00F8
	int32_t armor; //0x00FC
	char pad_0100[40]; //0x0100
	int32_t rifleAmmoReserved; //0x0128
	char pad_012C[8]; //0x012C
	int32_t dualPistolAmmoReserved; //0x0134
	char pad_0138[4]; //0x0138
	int32_t pistolAmmo; //0x013C
	char pad_0140[16]; //0x0140
	float rifleAmmo; //0x0150
	char pad_0154[4]; //0x0154
	int32_t nadesCount; //0x0158
	int32_t dualPistolAmmo; //0x015C
	char pad_0160[3808]; //0x0160
}; //Size: 0x1040