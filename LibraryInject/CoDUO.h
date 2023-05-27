#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <wtypes.h>

#include "coduo_structs.h"

#define gsc_function(name, callback) { name, { name, callback, 0 } }

namespace CoDUO
{
	inline std::unordered_map<std::string, gsc_function_t> gsc_functions
	{
	};

	inline std::unordered_map<std::string, gsc_function_t> gsc_methods
	{
	};

	inline DWORD uo_game_mp_x86 = 0;
	inline uint32_t CodeCallback_PlayerShoot = 0;

	inline refdef_t* refdef = nullptr;
	inline gentity_t* g_entities = nullptr;
	inline cvarTable_t* gameCvarTable = nullptr;
	inline cvar_t* cvar_indexes = nullptr;

	uint32_t Scr_LoadScript(const char* file);
	uint32_t Scr_GetFunctionHandle(const char* file, const char* method);
	uint32_t Scr_RunScript(uint32_t scriptHandle, uint32_t argc);

	void Scr_AddUndefined();
	void Scr_AddBool(bool value);
	void Scr_AddInt(int value);
	void Scr_AddFloat(float value);
	void Scr_AddVector(void* value);
	void Scr_AddString(const char* string);
	void Scr_AddEntity(int index);

	const char* SL_ConvertToString(int32_t index);

	cvar_t* Cvar_FindVar(const char* var_name);
	cvar_t* Cvar_Get(const char* var_name, const char* var_value, int flags);
	cvar_t* Cvar_Set(const char* var_name, const char* value, qboolean force);

	void BaseAttach();
	void uo_game_mp_x86_OnAttach();
	void uo_game_mp_x86_OnDetach();
};