#pragma once
#include <iostream>

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
	float armor; //0x00FC
	char pad_0100[60]; //0x0100
	int32_t pistolAmmo; //0x013C
	char pad_0140[16]; //0x0140
	int32_t rifleAmmo; //0x0150
	char pad_0154[4]; //0x0154
	int32_t nadesCount; //0x0158
	char pad_015C[44]; //0x015C
	int32_t meleeAtackCount; //0x0188
	int32_t pistolShotCount; //0x018C
	char pad_0190[16]; //0x0190
	int32_t rifleShotCount; //0x01A0
	char pad_01A4[3740]; //0x01A4
}; //Size: 0x1040

namespace Offset {
	DWORD localPlayerOffset = 0x109B74;
}