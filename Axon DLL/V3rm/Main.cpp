
#include "globals.h"
#include "Bridge.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <iterator>
#include <fstream>
#include <intrin.h>
#include <Tlhelp32.h>
#include <CommCtrl.h>
#include <Wininet.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <istream>
#include <iterator>
#include <sstream>
#pragma comment(lib, "wininet.lib")
using namespace std;

DWORD ScriptContext;
DWORD ScriptContextVFTable = x(0x1C890C8); // remember to update scriptcontext

DWORD grabGlobalStateIndex(DWORD ScriptContext, int idx)
{
	//(unsigned int)&v2[14 * v3 ^ 43] ^ v2[14 * v3 + 43];
	DWORD* context = reinterpret_cast<DWORD*>(ScriptContext);
	return context[14 * 0 ^ idx] ^ (DWORD)&context[14 * 0 ^ idx];
}
//24 addys
using Bridge::m_rL;
using Bridge::m_L;
void CreateConsole(const char* Name) {
	DWORD consoleOldProtect = 0;
	VirtualProtect(FreeConsole, 1, PAGE_EXECUTE_READWRITE, &consoleOldProtect);
	*(UINT*)FreeConsole = 0xC2;
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	DWORD cons = (WS_CAPTION | DS_MODALFRAME | WS_MINIMIZEBOX | WS_SYSMENU);
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, cons);
	SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
	SetConsoleTitleA(Name);
}
void PushGlobal(DWORD rL, lua_State* L, const char* s)
{
	r_lua_getglobal(rL, s);
	Bridge::push(rL, L, -1);
	std::cout << "Wrapped: " << s << "\n";
	lua_setglobal(L, s);
	r_lua_pop(rL, 1);
}
namespace Run {
	static std::vector<std::string> SplitArguments(std::string string)
	{
		std::vector<std::string> elements;
		std::stringstream start(string);
		std::istream_iterator<std::string> begin(start);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vectorStrings(begin, end);
		return vectorStrings;
	}
	std::string parse(const std::string& s,
		const std::string& start_delim,
		const std::string& stop_delim)
	{
		unsigned first_delim_pos = s.find(start_delim);
		unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
		unsigned last_delim_pos = s.find(stop_delim);

		return s.substr(end_pos_of_first_delim,
			last_delim_pos - end_pos_of_first_delim);
	}
}
DWORD WINAPI input(PVOID lvpParameter)
{
	string WholeScript = "";
	HANDLE hPipe;
	char buffer[999999];
	DWORD dwRead;
	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\sex"), // Change ur own pipe skid
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
		PIPE_WAIT,
		1,
		999999,
		999999,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);
	while (hPipe != INVALID_HANDLE_VALUE)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)
		{
			while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
			{
				buffer[dwRead] = '\0';
				try {
					try {
						WholeScript = WholeScript + buffer;
					}
					catch (...) {
					}
				}
				catch (std::exception e) {

				}
				catch (...) {

				}
			}
			if (WholeScript.find("console('") != std::string::npos)
			{
				std::string Script = Run::parse(WholeScript, "console('", "')");
			
				CreateConsole(Script.c_str());
			}
			else
			{
				if (WholeScript.find("printf('") != std::string::npos)
				{
					std::string Script = Run::parse(WholeScript, "printf('", "')");
					printf(Script.c_str());
				}
			}
			
			if (luaL_loadstring(m_L, WholeScript.c_str()))
				printf("Error: %s\n", lua_tostring(m_L, -1));
			else
				lua_pcall(m_L, 0, 0, 0);
		
		

			WholeScript = "";
		}
		DisconnectNamedPipe(hPipe);
	}
}


namespace Memory {
	BOOL compare(const BYTE* location, const BYTE* aob, const char* mask) {
		for (; *mask; ++aob, ++mask, ++location) {
			__try {
				if (*mask == 'x' && *location != *aob)
					return 0;
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				return 0;
			}
		}
		return 1;
	}

	DWORD find_Pattern(DWORD size, BYTE* pattern, char* mask,
		BYTE protection = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) {
		SYSTEM_INFO SI = { 0 };
		GetSystemInfo(&SI);
		DWORD start = (DWORD)SI.lpMinimumApplicationAddress;
		DWORD end = (DWORD)SI.lpMaximumApplicationAddress;
		MEMORY_BASIC_INFORMATION mbi;
		while (start < end && VirtualQuery((void*)start, &mbi, sizeof(mbi))) {
			// Make sure the memory is committed, matches our protection, and isn't PAGE_GUARD.
			if ((mbi.State & MEM_COMMIT) && (mbi.Protect & protection) && !(mbi.Protect & PAGE_GUARD)) {
				// Scan all the memory in the region.
				for (DWORD i = (DWORD)mbi.BaseAddress; i < (DWORD)mbi.BaseAddress + mbi.RegionSize; ++i) {
					if (compare((BYTE*)i, pattern, mask)) {
						return i;
					}
				}
			}
			// Move onto the next region of memory.
			start += mbi.RegionSize;
		}
		return 0;
	}

	int Scan(DWORD mode, char* content, char* mask) {
		return find_Pattern(0x7FFFFFFF, (BYTE*)content, mask, mode);
	}
}


int getRawMetaTable(lua_State *L) {
	Bridge::push(L, m_rL, 1);

	if (r_lua_getmetatable(m_rL, -1) == 0) {
		lua_pushnil(L);
		return 0;
	}
	Bridge::push(m_rL, L, -1);

	return 1;
}

static int UserDataGC(lua_State *Thread) {
	void *UD = lua_touserdata(Thread, 1);
	if (m_rL) {

		r_lua_rawgeti(m_rL, LUA_REGISTRYINDEX, (int)UD);
		if (r_lua_type(m_rL, -1) <= R_LUA_TNIL) {
			lua_pushnil(Thread);
			lua_rawseti(Thread, LUA_REGISTRYINDEX, (int)UD);

		}
	}
	return 0;
}
void GlobalsPushed()
{

	PushGlobal(m_rL, m_L, "DockWidgetPluginGuiInfo");
	PushGlobal(m_rL, m_L, "warn");
	PushGlobal(m_rL, m_L, "CFrame");
	PushGlobal(m_rL, m_L, "gcinfo");
	PushGlobal(m_rL, m_L, "DateTime");
	PushGlobal(m_rL, m_L, "tick");
	PushGlobal(m_rL, m_L, "bit32");
	PushGlobal(m_rL, m_L, "debug");
	PushGlobal(m_rL, m_L, "NumberSequence");
	PushGlobal(m_rL, m_L, "assert");
	PushGlobal(m_rL, m_L, "tonumber");
	PushGlobal(m_rL, m_L, "Color3");
	PushGlobal(m_rL, m_L, "Enum");
	PushGlobal(m_rL, m_L, "Delay");
	PushGlobal(m_rL, m_L, "Stats");
	PushGlobal(m_rL, m_L, "_G");
	PushGlobal(m_rL, m_L, "UserSettings");
	PushGlobal(m_rL, m_L, "coroutine");
	PushGlobal(m_rL, m_L, "NumberRange");
	PushGlobal(m_rL, m_L, "PhysicalProperties");
	PushGlobal(m_rL, m_L, "PluginManager");
	PushGlobal(m_rL, m_L, "Ray");
	PushGlobal(m_rL, m_L, "NumberSequenceKeypoint");
	PushGlobal(m_rL, m_L, "Version");
	PushGlobal(m_rL, m_L, "Vector2");
	PushGlobal(m_rL, m_L, "os");
	PushGlobal(m_rL, m_L, "Game");
	PushGlobal(m_rL, m_L, "delay");
	PushGlobal(m_rL, m_L, "spawn");
	PushGlobal(m_rL, m_L, "version");
	PushGlobal(m_rL, m_L, "string");
	PushGlobal(m_rL, m_L, "CellId");
	PushGlobal(m_rL, m_L, "stats");
	PushGlobal(m_rL, m_L, "typeof");
	PushGlobal(m_rL, m_L, "shared");
	PushGlobal(m_rL, m_L, "_VERSION");
	PushGlobal(m_rL, m_L, "LoadLibrary");
	PushGlobal(m_rL, m_L, "settings");
	PushGlobal(m_rL, m_L, "loadstring");
	PushGlobal(m_rL, m_L, "RaycastParams");
	PushGlobal(m_rL, m_L, "table");
	PushGlobal(m_rL, m_L, "TweenInfo");
	PushGlobal(m_rL, m_L, "printidentity");
	PushGlobal(m_rL, m_L, "require");
	PushGlobal(m_rL, m_L, "Vector3");
	PushGlobal(m_rL, m_L, "ypcall");
	PushGlobal(m_rL, m_L, "Vector3int16");
	PushGlobal(m_rL, m_L, "setmetatable");
	PushGlobal(m_rL, m_L, "next");
	PushGlobal(m_rL, m_L, "Wait");
	PushGlobal(m_rL, m_L, "wait");
	PushGlobal(m_rL, m_L, "Region3int16");
	PushGlobal(m_rL, m_L, "ipairs");
	PushGlobal(m_rL, m_L, "elapsedTime");
	PushGlobal(m_rL, m_L, "time");
	PushGlobal(m_rL, m_L, "rawequal");
	PushGlobal(m_rL, m_L, "Vector2int16");
	PushGlobal(m_rL, m_L, "collectgarbage");
	PushGlobal(m_rL, m_L, "game");
	PushGlobal(m_rL, m_L, "newproxy");
	PushGlobal(m_rL, m_L, "Spawn");
	PushGlobal(m_rL, m_L, "Workspace");
	PushGlobal(m_rL, m_L, "Region3");
	PushGlobal(m_rL, m_L, "utf8");
	PushGlobal(m_rL, m_L, "UDim2");
	PushGlobal(m_rL, m_L, "xpcall");
	PushGlobal(m_rL, m_L, "rawset");
	PushGlobal(m_rL, m_L, "PathWaypoint");
	PushGlobal(m_rL, m_L, "Instance");
	PushGlobal(m_rL, m_L, "tostring");
	PushGlobal(m_rL, m_L, "Random");
	PushGlobal(m_rL, m_L, "workspace");
	PushGlobal(m_rL, m_L, "unpack");
	PushGlobal(m_rL, m_L, "PluginDrag");
	PushGlobal(m_rL, m_L, "pcall");
	PushGlobal(m_rL, m_L, "getfenv");
	PushGlobal(m_rL, m_L, "ColorSequenceKeypoint");
	PushGlobal(m_rL, m_L, "type");
	PushGlobal(m_rL, m_L, "ColorSequence");
	PushGlobal(m_rL, m_L, "ElapsedTime");
	PushGlobal(m_rL, m_L, "select");
	PushGlobal(m_rL, m_L, "getmetatable");
	PushGlobal(m_rL, m_L, "Faces");
	PushGlobal(m_rL, m_L, "rawget");
	PushGlobal(m_rL, m_L, "UDim");
	PushGlobal(m_rL, m_L, "Rect");
	PushGlobal(m_rL, m_L, "BrickColor");
	PushGlobal(m_rL, m_L, "setfenv");
	PushGlobal(m_rL, m_L, "pairs");
	PushGlobal(m_rL, m_L, "Axes");
	PushGlobal(m_rL, m_L, "error");
	PushGlobal(m_rL, m_L, "print");

	printf("Wrapped!\n");
}

void main()
{
	CreateConsole("Axon stuff and stuff");
	//CreateConsole("updated by deluxe - AxOn oMg DeLuxE is A sKiD nOw");
	ScriptContext = Memory::Scan(PAGE_READWRITE, (char*)&ScriptContextVFTable, (char*)"xxxx");

	m_rL = *(DWORD*)(ScriptContext + 0xAC) + (ScriptContext + 0xAC); 
    printf("Lua State Passed!\n");
	m_L = luaL_newstate(); 
	DWORD LState = *(DWORD*)(ScriptContext + 0xAC) + (ScriptContext + 0xAC);
	Bridge::VehHandlerpush();
	luaL_openlibs(m_L);

	GlobalsPushed();
	

	lua_register(m_L, "getrawmetatable", getRawMetaTable); 
	lua_newtable(m_L);
	lua_setglobal(m_L, "_G"); 
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)input, NULL, NULL, NULL); 
	//printf("RVX INJECTED!\n"); 
	r_lua_getglobal(LState, "print");
	r_lua_pushstring(LState, "injected");
	r_lua_call(LState, 1, 0);
	printf("Axon loaded duhs\n");
	*reinterpret_cast<int*>(*reinterpret_cast<int*>(m_rL + 0x80) + 0x18) = 6; 
}



BOOL APIENTRY DllMain(HMODULE Module, DWORD Reason, void* Reserved)
{
	switch (Reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(Module);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	default: break;
	}

	return TRUE;
}