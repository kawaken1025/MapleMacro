/*--------------------------------------------------------------------------
* NekoAddon.dll メイン
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "comutil.h"
#include "NekoAddon.hpp"

CRITICAL_SECTION g_global_lock;
bool g_initialized = false;
HANDLE g_module;

// メッセー出力機構
utl::StringBuffer<char> g_message_body;

struct CriticalSection {
	CRITICAL_SECTION* plock;
	CriticalSection(CRITICAL_SECTION& lock) {
		plock = &lock;
		EnterCriticalSection(plock);
	}
	~CriticalSection() {
		LeaveCriticalSection(plock);
	}
};

extern "C" void __stdcall startup_neko()
{
	if(!g_initialized) {
		CriticalSection lock(g_global_lock);
		if(!g_initialized) {
			attach_neko();
			g_initialized = true;
		}
	}
}

extern "C" void __stdcall shutdown_neko()
{
	detach_neko();
	g_initialized = false;
}

extern "C" utl::StringBuffer<char>* __stdcall get_internal_message_buffer() {
	return &g_message_body;
}

BOOL APIENTRY DllMain(HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved)
{
	switch( ul_reason_for_call ) {
	case DLL_PROCESS_ATTACH:
		g_module = hModule;
		InitializeCriticalSection(&g_global_lock);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		DeleteCriticalSection(&g_global_lock);
		break;
	}
	return TRUE;
}
