
#include "sox_platform.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdio.h>

static int l_sox_init(lua_State *L)
{
	sox_p_result result = sox_p_init();

	if (!result.value)
	{
		lua_pushnil(L);
		lua_pushstring(L, result.error);
		return 2;
	}
	
	lua_pushboolean(L, true);
	return 1;
}

static int l_sox_shutdown(lua_State *L)
{
	sox_p_result result = sox_p_shutdown();

	if (!result.value)
	{
		lua_pushnil(L);
		lua_pushstring(L, result.error);
		return 2;
	}

	lua_pushboolean(L, true);
	return 1;
}

// socket class:
// new_socket(family, protocol)
// new_tcp_listener(local endpoint, blocking mode)
// new_tcp_stream(remote endpoint, blocking mode)
// new_udp_socket(local endpoint, blocking mode)

// set_blocking_mode
// bind
// listen
// connect
// accept
// select
// send, send_to
// receive, receive_from
// close
// is_open

typedef struct sox_socket
{
	sox_p_socket_t handle;
}
sox_socket;

static bool sox_socket_is_open(sox_socket const* s)
{
	return s->handle != SOX_P_INVALID_SOCKET;
}

#define SOX_SOCKET_MT_NAME "sox.socket"

static int l_sox_socket_open(lua_State *L)
{
	// todo: get family
	// todo: get protocol

	sox_p_socket_result result = sox_p_socket();

	if (result.value == SOX_P_INVALID_SOCKET)
	{
		lua_pushnil(L);
		lua_pushstring(L, result.error);
		return 2;
	}

	sox_socket *socket_ud = lua_newuserdata(L, sizeof(sox_socket));
	socket_ud->handle = result.value;

	luaL_getmetatable(L, SOX_SOCKET_MT_NAME);
	lua_setmetatable(L, -2);

	return 1;
}

static int l_sox_socket_is_open(lua_State *L)
{
	sox_socket *socket_ud = luaL_checkudata(L, 1, SOX_SOCKET_MT_NAME);

	lua_pushboolean(L, sox_socket_is_open(socket_ud));
	return 1;
}

static int l_sox_socket_close(lua_State *L)
{
	printf("close\n");

	sox_socket *socket_ud = luaL_checkudata(L, 1, SOX_SOCKET_MT_NAME);

	if (!sox_socket_is_open(socket_ud))
	{
		lua_pushboolean(L, true);
		return 1;
	}

	sox_p_close_socket_result result = sox_p_close_socket(socket_ud->handle);

	if (!result.value)
	{
		lua_pushnil(L);
		lua_pushstring(L, result.error);
		return 2;
	}

	lua_pushboolean(L, true);
	return 1;
}

static const struct luaL_Reg reg[] =
{
	{ "init", l_sox_init },
	{ "shutdown", l_sox_shutdown },
	{ "open_socket", l_sox_socket_open },
	{ NULL, NULL },
};

static const struct luaL_Reg reg_m[] =
{
	{ "is_open", l_sox_socket_is_open },
	{ "close", l_sox_socket_close },
	{ NULL, NULL },
};

int luaopen_sox(lua_State *L)
{
	luaL_newmetatable(L, SOX_SOCKET_MT_NAME);
	
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	lua_pushcfunction(L, l_sox_socket_close);
	lua_setfield(L, -2, "__close");
	
	lua_pushcfunction(L, l_sox_socket_close);
	lua_setfield(L, -2, "__gc");

	luaL_setfuncs(L, reg_m, 0);

	luaL_newlib(L, reg);
	return 1;
}
