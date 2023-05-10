#include <Windows.h>
#include <iostream>

#include "WinApiHelper.h"
#include "OpenGLHelper.h"
#include "ImGuiManager.h"

DWORD WINAPI MainThread(LPVOID param)
{
	WinApiHelper::CreateConsole("Console");

	WinApiHelper::InjectDetours();
	OpenGLHelper::InjectDetours();

	while (true)
	{
		Sleep(1);
	}

	ImGuiManager::Dispose();

	//FreeLibraryAndExitThread((HMODULE)param, 0);

	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, MainThread, hModule, 0, 0);
		DisableThreadLibraryCalls(hModule);
	}

	return TRUE;
}