#pragma once
#include <cstdint>
#include <wtypes.h>
#include "CoDUO_Callbacks.h"

namespace CoDUO
{
	inline DWORD syscall = 0x004685A0;

	inline DWORD uo_game_mp_x86 = 0;
	inline uint32_t CodeCallback_OnPlayerShoot = 0;
	inline uint32_t CodeCallback_OnProjectileBounce = 0;

	inline refdef_t* refdef = nullptr;
	inline gentity_t* g_entities = nullptr;
	inline cvarTable_t* gameCvarTable = nullptr;
	inline cvar_t* cvar_indexes = nullptr;

	int32_t Scr_LoadScript(const char* file);
	int32_t Scr_GetFunctionHandle(const char* file, const char* method);
	int32_t Scr_RunScript(int32_t scriptHandle, uint32_t argc);

	int32_t Scr_GetNumParam();
	int32_t Scr_GetType(int param);
	int32_t Scr_GetInt(int param);
	float Scr_GetFloat(int param);
	void Scr_GetVector(int param, void* destination);
	vec3_t Scr_GetVector(int param);
	const char* Scr_GetString(int param);
	int32_t Scr_GetConstString(int param);
	gentity_t* Scr_GetEntity(int param);

	void Scr_AddUndefined();
	void Scr_AddBool(bool value);
	void Scr_AddInt(int value);
	void Scr_AddFloat(float value);
	void Scr_AddVector(float* value);
	void Scr_AddString(const char* string);
	void Scr_AddEntityNum(int index);
	void Scr_MakeArray();
	void Scr_AddArray();
	void Scr_AddArrayStringIndexed(int32_t str_index);

	int32_t G_NewString(const char* string);
	const char* SL_ConvertToString(int32_t index);

	void G_GetPlayerViewOrigin(gentity_t* ent, float* destination);

	void trap_GetUserinfo(int num, char* buffer, int bufferSize);
	void trap_SetUserinfo(int num, const char* buffer);
	const char* Info_ValueForKey(const char* buffer, const char* key);
	void Info_SetValueForKey(char* buffer, const char* key, const char* value);

	void trap_SendConsoleCommand(int exec_when, const char* text);
	void Cmd_AddCommand(const char* cmd_name, void* function);
	cvar_t* Cvar_FindVar(const char* var_name);
	cvar_t* Cvar_Get(const char* var_name, const char* var_value, int flags);
	cvar_t* Cvar_Set(const char* var_name, const char* value, qboolean force);

	void BaseAttach();
	void uo_game_mp_x86_OnAttach();
	void uo_game_mp_x86_OnDetach();
};