# AssaultCube-Hack
My journey to reverse engineering and writing cheat. I will try to update as my journey goes on!

## Reverse Engineer to find offset
Tool: Cheat Engine & Reclass

### Finding Local Player offset

> You can do that by scanning for health or ammo value then see what accesses the address, perform pointer scan to check and validate the correct pointer.
We can get the offset via that pointer in CE.

### Heading to Reclass

> Paste the pointer we found into Reclass, we get access to struct/class LocalPlayer.

> Then mess around the game and see which address is doing and use your head to figure that out.

![image](https://github.com/nmkha16/AssaultCube-Hack/assets/91834063/bc2f2d62-a03a-4dcb-97c6-567b4f64fc24)

> If you can't find certain variables such as Health or Ammo or Armor, perform scan in CE and see what step offset, then go back to Reclass to jump to that offset.

#### Use Code Generator to make a struct of Local Player

![image](https://github.com/nmkha16/AssaultCube-Hack/assets/91834063/4838e9ab-8676-4dda-8a5e-43536fca0c78)

> Here is what I have found

## Programming Cheat

**Get Local Player Pointer by adding _Base Address of Module_ and _offset of Local Player_**

# **I WILL UPDATE MORE ON THE JOURNEY**
