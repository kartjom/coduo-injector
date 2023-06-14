#pragma once
#include <string>
#include <unordered_map>
#include "coduo_structs.h"

namespace CoDUO::Gsc
{
	void Scr_StringToCmd();
	void Scr_LuaDoFile();
	void Scr_LuaDoString();

	void Scr_ForceRename(int param);
	void Scr_GetViewOrigin(int param);
	void Scr_GetViewAngles(int param);
	void Scr_GetParent(int param);
	void Scr_GetOwner(int param);

	inline std::unordered_map<std::string, gsc_function_t> gsc_functions
	{
		gsc_function("console", Scr_StringToCmd),
		gsc_function("lua_dofile", Scr_LuaDoFile),
		gsc_function("lua_dostring", Scr_LuaDoString),
	};

	inline std::unordered_map<std::string, gsc_function_t> gsc_methods
	{
		gsc_function("rename", Scr_ForceRename),
		gsc_function("getvieworigin", Scr_GetViewOrigin),
		gsc_function("getviewangles", Scr_GetViewAngles),
		gsc_function("getparent", Scr_GetParent),
		gsc_function("getowner", Scr_GetOwner),
	};
}