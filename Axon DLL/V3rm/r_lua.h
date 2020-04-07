#pragma once
#include <Windows.h>
#include "globals.h"
#include "retcheck.h"

#include "DeLuxeAxon.h"
#define r_lua_tostring(rL,i)	r_lua_tolstring(rL, (i), NULL)
#define r_lua_pop(rL,n)		r_lua_settop(rL, -(n)-1)
#define r_lua_getglobal(rL,s)	r_lua_getfield(rL, LUA_GLOBALSINDEX, (s))
#define r_lua_newtable(rL) r_lua_createtable(rL, 0, 0)

typedef void(CCVgetfield* rgetfield)(DWORD rL, int idx, const char *k);
rgetfield r_lua_getfield = (rgetfield)unprotect(x(ADDYgetfield)); // Gets address from one of the header files, idk seems easier to update from another file. 
// Open the folder called Header Files and open DeLuxeAxon.h. You'll find what you need to update there, incuding addys and callingconvs
// Go to golbals.h to update the globals
// All addresses from XDumper, join their discord here https://discord.gg/mXWPyTn since I'm too lazy to create a tutorial on how to unpack and use IDA to find RBLX addys
// Anyways enjoy skidding I won't bother teaching how to add custom functions

typedef char*(CCVtolstring* rtolstring)(DWORD rL, int idx, size_t *size);
rtolstring r_lua_tolstring = (rtolstring)(unprotect(x(ADDYtolstring)));

typedef void(CCVsettop* rsettop)(DWORD rL, int idx);
rsettop r_lua_settop = (rsettop)(unprotect(x(ADDYsettop)));

typedef bool(CCVtoboolean* toboolean)(DWORD rL, bool idx);
toboolean r_lua_toboolean = (toboolean)(x(ADDYtoboolean));

typedef void(CCVpushvalue* pushvalue)(DWORD rL, DWORD idx);
pushvalue r_lua_pushvalue = (pushvalue)(unprotect(x(ADDYpushvalue)));

typedef double(CCVpushnumber* pushnumber)(DWORD rL, double idx);
pushnumber r_lua_pushnumber = (pushnumber)(unprotect(x(ADDYpushnumber)));

typedef void(CCVcall* acall)(DWORD a1, int a2, int a3);
acall r_lua_call = (acall)unprotect(x(ADDYcall));

typedef void(CCVpushstring* rpushstring)(DWORD rL, const char*);
rpushstring r_lua_pushstring = (rpushstring)(x(ADDYpushstring));

typedef int(CCVpcall* pcall)(DWORD rL, DWORD, DWORD, DWORD);
pcall r_lua_pcall = (pcall)(unprotect(x(ADDYpcall)));

typedef void(CCVpushnil* pushnil)(DWORD);
pushnil r_lua_pushnil = (pushnil)(unprotect(x(ADDYpushnil)));

typedef DWORD(CCVnext* next2)(DWORD rL, int idx);
next2 r_lua_next = (next2)(unprotect(x(ADDYnext)));

typedef bool(CCVpushvalue* rboolean)(unsigned int, bool);	
rboolean r_lua_pushboolean = (rboolean)(unprotect(x(ADDYpushvalue)));

typedef double(CCVtonumber* rtonumber)(DWORD, int);
rtonumber r_lua_tonumber = (rtonumber)(x(ADDYtonumber));

typedef void(CCVpushcclosure* rpushcclosure)(DWORD rL, int fn, int non);
rpushcclosure r_lua_pushcclosure = (rpushcclosure)(unprotect(x(ADDYpushcclosure)));

typedef void(CCVcreatetable*rcreatetable)(DWORD rL, int num, int fix);
rcreatetable r_lua_createtable = (rcreatetable)(unprotect(x(ADDYcreatetable)));

typedef void*(CCVnewuserdata *rnewuserdata)(DWORD rL, int idx);
rnewuserdata r_lua_newuserdata = (rnewuserdata)(unprotect(x(ADDYnewuserdata)));

typedef void*(CCVgetmetatable *rgetmetatable)(DWORD rL, int idx);
rgetmetatable r_lua_getmetatable = (rgetmetatable)(unprotect(x(ADDYgetmetatable)));

typedef void*(CCVsettable *rsettable)(DWORD rL, int);
rsettable r_lua_settable = (rsettable)(unprotect(x(ADDYsettable)));

typedef DWORD(CCVtype *rtype)(DWORD, int);
rtype r_lua_type = (rtype)(x(ADDYtype));

typedef DWORD(CCVnewthread *rnewthread)(DWORD);
rnewthread r_lua_newthread = (rnewthread)unprotect(x(ADDYnewthread));

typedef DWORD(CVCVref *rref)(DWORD, DWORD);
rref r_luaL_ref = (rref)unprotect(x(ADDYLref));

typedef void(CCVrawgeti *rrawgeti)(DWORD, DWORD, DWORD);
rrawgeti r_lua_rawgeti = (rrawgeti)unprotect(x(ADDYrawgeti));

typedef int(CCVgettop *gettop)(DWORD);
gettop r_lua_gettop = (gettop)(x(ADDYgettop));

typedef void(CCVpushlightuserdata *rpushlight)(DWORD, void*);
rpushlight r_lua_pushlightuserdata = (rpushlight)(unprotect(x(ADDYpushlightuserdata)));

typedef void*(CCVtouserdata *touserdata)(DWORD, int);
touserdata r_lua_touserdata =(touserdata)unprotect(x(ADDYtouserdata));
