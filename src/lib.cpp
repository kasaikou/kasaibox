#include <lua.hpp>

int area(lua_State* L) {
	int w = static_cast<int>(lua_tointeger(L, 1));
	int h = static_cast<int>(lua_tointeger(L, 2));

	lua_pushnumber(L, static_cast<lua_Number>(w * h));
	lua_pushstring(L, "");
	return 2;
}

static luaL_Reg functions[] = {
	{"area", area},
	{nullptr, nullptr} };

extern "C" __declspec(dllexport) int luaopen_kasaibox(lua_State * L) {
	luaL_register(L, "kasaibox", functions);
	return 1;
}
