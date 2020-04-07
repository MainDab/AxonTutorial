#pragma once
#define x(x) (x - 0x400000 + (DWORD)GetModuleHandleA(0)) // no touch
// remember to update these globals. I just changed them to 69 for the sake of showing you guys how to do it
// 69 for ya know hehheheheheh 
#define R_LUA_TNIL 0
#define R_LUA_TLIGHTUSERDATA 3
#define R_LUA_TNUMBER 2
#define R_LUA_TBOOLEAN 1
#define R_LUA_TSTRING 4
#define R_LUA_TTHREAD 7
#define R_LUA_TFUNCTION 8
#define R_LUA_TTABLE 5
#define R_LUA_TUSERDATA 6
#define R_LUA_TPROTO 9
#define R_LUA_TUPVALUE 10