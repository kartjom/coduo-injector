#include "Detours.h"
#include "CoDUO.h"
#include <stdio.h>

using namespace CoDUO;
using namespace CoDUO::Gsc;

void* GetFunctionCallback(const char* value)
{
	if (gsc_functions.find(value) != gsc_functions.end())
	{
		return gsc_functions[value].callback;
	}

	return 0;
}

void* GetMethodCallback(const char* value)
{
	if (gsc_methods.find(value) != gsc_methods.end())
	{
		return gsc_methods[value].callback;
	}

	return 0;
}

namespace Detours
{
	ImplementDetour(GScr_LoadGameTypeScript)
	{
		_asm pushad

		if (Scr_LoadScript("maps/mp/gametypes/_callbacksetup"))
		{
			CodeCallback.OnPlayerShoot = Scr_GetFunctionHandle("maps/mp/gametypes/_callbacksetup", "CodeCallback_OnPlayerShoot");
			CodeCallback.OnPlayerMelee = Scr_GetFunctionHandle("maps/mp/gametypes/_callbacksetup", "CodeCallback_OnPlayerMelee");
			CodeCallback.OnProjectileBounce = Scr_GetFunctionHandle("maps/mp/gametypes/_callbacksetup", "CodeCallback_OnProjectileBounce");
			CodeCallback.OnProjectileExplode = Scr_GetFunctionHandle("maps/mp/gametypes/_callbacksetup", "CodeCallback_OnProjectileExplode");
		}

		_asm popad

		_restore
		{
			sub esp, 0x44

			mov eax, uo_game_mp_x86
			add eax, 0x00082650

			mov eax,[eax]
		}

		JumpBack(GScr_LoadGameTypeScript)
	}

	ImplementDetour(ShootCallback)
	{
		_asm pushad

		if (CodeCallback.OnPlayerShoot != 0)
		{
			gentity_t* player = nullptr;
			const char* weaponName = nullptr;

			_asm
			{
				mov player, edi
				mov edx, [edx + 4]
				mov weaponName, edx
			}

			if (player && weaponName && player->client)
			{
				Scr_AddString(weaponName);
				Scr_AddVector(player->client->viewangles);

				vec3_t vieworigin;
				G_GetPlayerViewOrigin(player, vieworigin);
				Scr_AddVector(vieworigin);

				Scr_AddEntityNum(player->number);
				Scr_RunScript(CodeCallback.OnPlayerShoot, 4);
			}
		}

		_asm popad

		_restore
		{
			mov eax, dword ptr ss : [ebp + 0x160]
		}

		JumpBack(ShootCallback)
	}

	ImplementDetour(MeleeCallback)
	{
		_asm pushad

		if (CodeCallback.OnPlayerMelee != 0)
		{
			gentity_t* player = nullptr;
			int16_t target_num = -1;

			_asm
			{
				mov player, ebp

				mov eax, [esp + 0x8C]
				mov target_num, ax
			}

			if (player)
			{
				if (target_num >= 0 && target_num < WORLDSPAWN)
				{
					Scr_AddEntityNum(g_entities[target_num].number);
				}
				else
				{
					Scr_AddUndefined();
				}

				Scr_AddEntityNum(player->number);
				Scr_RunScript(CodeCallback.OnPlayerMelee, 2);
			}
		}

		_asm popad

		_restore
		{
			add esp, 0x2C
			test al, 0x10
		}

		JumpBack(MeleeCallback)
	}

	ImplementDetour(ProjectileBounceCallback)
	{
		_asm pushad

		if (CodeCallback.OnProjectileBounce)
		{
			gentity_t* projectile = nullptr;

			_asm
			{
				mov projectile, ebp
			}

			if (projectile)
			{
				Scr_AddEntityNum(projectile->number);
				Scr_RunScript(CodeCallback.OnProjectileBounce, 1);
			}
		}

		_asm popad

		_restore
		{
			mov eax, dword ptr ss:[esp + 0x44]
			push edi
		}

		JumpBack(ProjectileBounceCallback)
	}

	ImplementDetour(ProjectileExplodeCallback)
	{
		_asm pushad

		if (CodeCallback.OnProjectileExplode)
		{
			gentity_t* projectile = nullptr;

			_asm
			{
				mov projectile, ebp
			}

			if (projectile)
			{
				Scr_AddEntityNum(projectile->number);
				Scr_RunScript(CodeCallback.OnProjectileExplode, 1);
			}
		}

		_asm popad

		_restore
		{
			sub esp, 0x54
			push ebx
			push ebp
		}

		JumpBack(ProjectileExplodeCallback);
	}
	
	ImplementDetour(LoadFunctionMP)
	{
		_asm sub esp, 0x4
		_asm pushad

		_asm
		{
			mov eax, [esp + 0x28]
			mov eax, [eax]
			push eax
			call GetFunctionCallback
			add esp, 0x4

			mov [esp + 0x20], eax
		}

		_asm popad

		_asm
		{
			pop eax
			cmp eax, 0
			jne function_found
		}

		_restore
		{
			mov eax, dword ptr ss:[esp + 0x4]
			mov edx, dword ptr ds:[eax]
		}

		JumpBack(LoadFunctionMP)

		_asm
		{
			function_found:
			ret
		}
	}

	ImplementDetour(LoadMethodMP)
	{
		_asm sub esp, 0x4
		_asm pushad
			
		_asm
		{
			mov eax, [esp + 0x28]
			mov eax, [eax]
			push eax
			call GetMethodCallback
			add esp, 0x4

			mov [esp + 0x20], eax
		}

		_asm popad
		
		_asm
		{
			pop eax
			cmp eax, 0
			jne method_found
		}

		_restore
		{
			mov eax, dword ptr ss:[esp + 0x8]
			mov edx, dword ptr ss:[esp + 0x4]
		}

		JumpBack(LoadMethodMP)

		_asm
		{
			method_found:
			ret
		}
	}
}