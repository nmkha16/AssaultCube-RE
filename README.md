# AssaultCube-RE
My journey to reverse engineering.

# DISCLAIMER
**I do not tolerate any kind of cheating in multiplayer game to gain advantages over other players. This program is made for purely education purpose.**

# Note
**Cheats only works for _AssaultCube v1.2.0.2_, offset may changes in other versions.**

## Reverse Engineer to find offset
Tool: Cheat Engine & Reclass

### Finding Local Player offset

You can do that by scanning for health or ammo value then see what accesses the address, perform pointer scan to check and validate the correct pointer.
We can get the offset via that pointer in `Cheat Engine`.

**Pointer**

```
Local Player Pointer: <ac_client.exe> + 0x00109B74
Local Player Current Weapon Pointer: <ac_client.exe> + 0x00109B74 + 0x374
```

**Offset Class Local Player**

```
Position (x, y, z) : float : {0x4; 0x8; 0xC}
View (pitch, yaw, roll) : float : {0x40; 0x44; 0x48}
Health : int : 0xF8
Armor : int : 0xFC
Pistol Ammo : int : 0x13C
Rifle Ammo : int : 0x150
Nade Count : int : 0x158
Dual Pistol Ammo : int : 0x15C
Current Weapon Pointer : 0x374
```

**Ofsset Class Weapon**

```
Ammo : int : 0x14
```

### Heading to Reclass

Paste the pointer we found into `Reclass`, we get access to struct/class LocalPlayer.

Then mess around the game and see which address is doing and use your head to figure that out.

![image](https://github.com/nmkha16/AssaultCube-Hack/assets/91834063/bc2f2d62-a03a-4dcb-97c6-567b4f64fc24)

If you can't find certain variables such as Health or Ammo or Armor, perform scan in `Cheat Engine` and see what step offset, then go back to Reclass to jump to that offset.

#### Use Code Generator to make a struct of Local Player

![image](https://github.com/nmkha16/AssaultCube-Hack/assets/91834063/4838e9ab-8676-4dda-8a5e-43536fca0c78)

Here is what I have found

## Programming Cheat

**Get Local Player Pointer by adding _Base Address of Module_ and _offset of Local Player_**

Use struct we got from `Reclass` to modifying value

We can only freeze value by constantly writing to it.

#### My first trainer:

![image](https://github.com/nmkha16/AssaultCube-Hack/assets/91834063/fdc8bcd0-7870-49ff-ba0e-c96297f3b65d)

### Update

I found a pointer to current weapon address that has current ammo on equiped gun => freeze this value to achieve infinite ammo on every gun. (Much better than old method)

