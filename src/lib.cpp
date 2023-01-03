#include <lua.hpp>
#include <memory>

std::unique_ptr<int, std::default_delete<int>> num_called = nullptr;

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

static luaL_Reg functions[] = {
	{"area", area},
	{"count_called", count_called},
	{nullptr, nullptr} };

extern "C" __declspec(dllexport) int luaopen_kasaibox(lua_State * L) {
	luaL_register(L, "kasaibox", functions);
	return 1;
}
