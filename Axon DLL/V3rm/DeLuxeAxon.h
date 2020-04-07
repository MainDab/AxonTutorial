#pragma once
#include <Windows.h>
// update these addresses skid
DWORD ADDYatpanic = 0x7CCC80;
DWORD ADDYcall = 0x7CCD10;
DWORD ADDYcheckstack = 0x7CCD10;
DWORD ADDYclose = 0x7CCE70;
DWORD ADDYconcat = 0x7CCEE0;
DWORD ADDYcreatetable = 0x7CCFB0;
DWORD ADDYerror = 0x7CD050;
DWORD ADDYgc = 0x7CD060;
DWORD ADDYgetfenv = 0x7CD320;
DWORD ADDYgetfield = 0x7CD3E0;
DWORD ADDYgethook = 0x7CD4A0;
DWORD ADDYgetinfo = 0x7CD4D0;
DWORD ADDYgetlocal = 0x7CD5F0;
DWORD ADDYgetmetatable = 0x7CD770;
DWORD ADDYgetstack = 0x7CD840;
DWORD ADDYgettable = 0x7CD980;
DWORD ADDYgettop = 0x7CDA00;
DWORD ADDYgetupvalue = 0x7CDA20;
DWORD ADDYinsert = 0x7CDAD0;
DWORD ADDYiscfunction = 0x7CDB80;
DWORD ADDYisstring = 0x7CDBB0;
DWORD ADDYisnumber = 0x7CDC00;
DWORD ADDYnewstate = 0x7CDC30;
DWORD ADDYnewthread = 0x7CDE20;
DWORD ADDYnewuserdata = 0x7CDF60;
DWORD ADDYnext = 0x7CE090;
DWORD ADDYobjlen = 0x7CE220;
DWORD ADDYpcall = 0x7CE300;
DWORD ADDYpushboolean = 0x7CE3D0;
DWORD ADDYpushcclosure = 0x7CE450;
DWORD ADDYpushfstring = 0x7CE600;
DWORD ADDYpushinteger = 0x7CE6A0;
DWORD ADDYpushlightuserdata = 0x7CE730;
DWORD ADDYpushlstring = 0x7CE7B0;
DWORD ADDYpushnil = 0x7CE850;
DWORD ADDYpushnumber = 0x7CE8C0;
DWORD ADDYpushstring = 0x7CE950;
DWORD ADDYpushthread = 0x7CE990;
DWORD ADDYpushvalue = 0x7CEAC0;
DWORD ADDYpushvfstring = 0x7CEB50;
DWORD ADDYrawequal = 0x7CEBF0;
DWORD ADDYrawget = 0x7CEC30;
DWORD ADDYrawgeti = 0x7CED80;
DWORD ADDYrawset = 0x7CEE10;
DWORD ADDYrawseti = 0x7CEF10;
DWORD ADDYremove = 0x7CF010;
DWORD ADDYreplace = 0x7CF0B0;
DWORD ADDYresume = 0x7CF1D0;
DWORD ADDYsetfenv = 0x7CF4F0;
DWORD ADDYsetfield = 0x7CF5E0;
DWORD ADDYsethook = 0x7CF6A0;
DWORD ADDYsetlocal = 0x7CF6D0;
DWORD ADDYsetmetatable = 0x7CF860;
DWORD ADDYsetreadonly = 0x7CF990;
DWORD ADDYsettable = 0x7CFA90;
DWORD ADDYsettop = 0x7CFB20;
DWORD ADDYsetupvalue = 0x7CFBD0;
DWORD ADDYtoboolean = 0x7CFCA0;
DWORD ADDYtointeger = 0x7CFCD0;
DWORD ADDYtolstring = 0x7CFD60;
DWORD ADDYtonumber = 0x7CFEA0;
DWORD ADDYtopointer = 0x7CFF30;
DWORD ADDYtostring = 0x7CFFA0;
DWORD ADDYtothread = 0x7CFFE0;
DWORD ADDYtouserdata = 0x7D0000;
DWORD ADDYtype = 0x7D0060;
DWORD ADDYtypename = 0x7D0090;
DWORD ADDYxmove = 0x7D00B0;
DWORD ADDYyield = 0x7D0170;
DWORD ADDYVexecute = 0x7C99F0;
DWORD ADDYVgettable = 0x7CC440;
DWORD ADDYVlessequal = 0x7CC5D0;
DWORD ADDYVlessthan = 0x7CC670;
DWORD ADDYVsettable = 0x7CC6F0;
DWORD ADDYVtonumber = 0x7C99F0;
DWORD ADDYVtostring = 0x7C9170;
DWORD ADDYSnewlstr = 0x7C8D00;
DWORD ADDYSnewudata = 0x7C8D00;
DWORD ADDYLaddlstring = 0x7C7B30;
DWORD ADDYLaddvalue = 0x7C7BA0;
DWORD ADDYLargerror = 0x7C7C20;
DWORD ADDYLcheckinteger = 0x7C7D70;
DWORD ADDYLchecklstring = 0x7C7E00;
DWORD ADDYLchecknumber = 0x7C7E30;
DWORD ADDYLcheckoption = 0x7C7ED0;
DWORD ADDYLchecktype = 0x7C7F10;
DWORD ADDYLerror = 0x7C7FE0;
DWORD ADDYLfindtable = 0x7C8010;
DWORD ADDYLgetmetafield = 0x7C8150;
DWORD ADDYLoptinteger = 0x7C81C0;
DWORD ADDYLoptlstring = 0x7C8200;
DWORD ADDYLoptnumber = 0x7C8270;
DWORD ADDYLref = 0x7C82C0;
DWORD ADDYLregister = 0x7C83D0;
DWORD ADDYLtypename = 0x7C84C0;
DWORD ADDYLtyperror = 0x7C8590;
DWORD ADDYLunref = 0x7C85D0;
DWORD ADDYLwhere = 0x7C8630;
// not all of them are _cdecl idiot, i just changed them so you lean how to update in this tutorial 
#define CCVatpanic __cdecl
#define CCVcall __cdecl
#define CCVcheckstack __cdecl
#define CCVclose __cdecl
#define CCVconcat __cdecl
#define CCVcreatetable __cdecl
#define CCVerror __cdecl
#define CCVgc __cdecl
#define CCVgetfenv __cdecl
#define CCVgetfield __cdecl
#define CCVgethook __cdecl
#define CCVgetinfo __cdecl
#define CCVgetlocal __cdecl
#define CCVgetmetatable _stdcall
#define CCVgetstack __cdecl
#define CCVgettable __cdecl
#define CCVgettop __cdecl
#define CCVgetupvalue _fastcall
#define CCVinsert __cdecl
#define CCViscfunction __cdecl
#define CCVisstring __cdecl
#define CCVisnumber __cdecl
#define CCVnewstate __cdecl
#define CCVnewthread __cdecl
#define CCVnewuserdata __cdecl
#define CCVnext __cdecl
#define CCVobjlen __cdecl
#define CCVpcall __cdecl
#define CCVpushboolean __cdecl
#define CCVpushcclosure _fastcall
#define CCVpushfstring __cdecl
#define CCVpushinteger __cdecl
#define CCVpushlightuserdata __cdecl
#define CCVpushlstring __cdecl
#define CCVpushnil __cdecl
#define CCVpushnumber _stdcall
#define CCVpushstring __cdecl
#define CCVpushthread __cdecl
#define CCVpushvalue _stdcall
#define CCVpushvfstring __cdecl
#define CCVrawequal __cdecl
#define CCVrawget __cdecl
#define CCVrawgeti __cdecl
#define CCVrawset _fastcall
#define CCVrawseti _fastcall
#define CCVremove __cdecl
#define CCVreplace __cdecl
#define CCVresume __cdecl
#define CCVsetfenv __cdecl
#define CCVsetfield __cdecl
#define CCVsethook __cdecl
#define CCVsetlocal __cdecl
#define CCVsetmetatable __cdecl
#define CCVsetreadonly __cdecl
#define CCVsettable __cdecl
#define CCVsettop __cdecl
#define CCVsetupvalue __cdecl
#define CCVtoboolean __cdecl
#define CCVtointeger __cdecl
#define CCVtolstring _fastcall
#define CCVtonumber __cdecl
#define CCVtopointer __cdecl
#define CCVtostring __cdecl
#define CCVtothread __cdecl
#define CCVtouserdata __cdecl
#define CCVtype __cdecl
#define CCVtypename __cdecl
#define CCVxmove __cdecl
#define CCVyield __cdecl
#define CVCVexecute __cdecl
#define CVCVgettable _cdecl
#define CVCVlessequal __cdecl
#define CVCVlessthan __cdecl
#define CVCVsettable __cdecl
#define CVCVtonumber __cdecl 
#define CVCVtostring __cdecl 
#define CVCVnewlstr _fastcall
#define CVCVnewudata _fastcall
#define CVCVaddlstring __cdecl
#define CVCVaddvalue __cdecl
#define CVCVargerror __cdecl
#define CVCVcheckinteger __cdecl
#define CVCVchecklstring __cdecl
#define CVCVchecknumber __cdecl
#define CVCVcheckoption _fastcall
#define CVCVchecktype __cdecl
#define CVCVerror __cdecl
#define CVCVfindtable __cdecl
#define CVCVgetmetafield __cdecl
#define CVCVoptinteger __cdecl
#define CVCVoptlstring __cdecl
#define CVCVoptnumber __cdecl
#define CVCVref __cdecl
#define CVCVregister __cdecl
#define CVCVtypename _fastcall	
#define CVCVtyperror _fastcall
#define CVCVunref __cdecl
#define CVCVwhere __cdecl