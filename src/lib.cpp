#include "lib.h"

std::unique_ptr<int, std::default_delete<int>> num_called = nullptr;
std::string dlldirpath;

int area(lua_State* L) {
	int w = static_cast<int>(lua_tointeger(L, 1));
	int h = static_cast<int>(lua_tointeger(L, 2));

	lua_pushnumber(L, static_cast<lua_Number>(w * h));
	lua_pushstring(L, "");
	return 2;
}

int count_called(lua_State* L) {
	if (num_called == nullptr) {
		num_called = std::make_unique<int>(0);
	}
	(*num_called)++;
	lua_pushnumber(L, static_cast<lua_Number>(*num_called));
	lua_pushstring(L, "");
	return 2;
}

int print_dlldirpath(lua_State* L) {
	lua_pushstring(L, dlldirpath.data());
	return 1;
}

int lua_opencv_binalize(lua_State* L) {
	auto data = reinterpret_cast<ARGB*>(lua_touserdata(L, 1));
	int w = static_cast<int>(lua_tointeger(L, 2));
	int h = static_cast<int>(lua_tointeger(L, 3));

	auto msg = opencv_binalization(data, w,	h, RGB(0x000000), RGB(0xFFFFFF), 0);
	lua_pushstring(L, msg.data());
	return 1;
}

static luaL_Reg functions[] = {
	{"area", area},
	{"count_called", count_called},
	{"print_dlldirpath", print_dlldirpath},
	{"opencv_binalize", lua_opencv_binalize},
	{nullptr, nullptr} };

extern "C" __declspec(dllexport) int luaopen_kasaibox(lua_State * L) {
	luaL_register(L, "kasaibox", functions);
	return 1;
}

#include <Windows.h>
#include <filesystem>

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		TCHAR dllpath[MAX_PATH + 1];
		GetModuleFileName(hInstDll, dllpath, MAX_PATH);
		std::filesystem::path p(dllpath);
		dlldirpath = p.parent_path().string();
		SetDllDirectory(dlldirpath.data());
	}

	return TRUE;
}
