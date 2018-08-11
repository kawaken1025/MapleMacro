/*--------------------------------------------------------------------------
* ChkImgEx.dll メイン
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#pragma once

#include <Windows.h>
#include "NekoAddon.h"
#include <stdlib.h>
#include <imagehlp.h>
#pragma comment( lib, "imagehlp.lib" )

utl::SharedStringBuffer<char> g_message;
bool g_symbol_available = false;

void throw_exception(const char* format, ...) {
	char buf[300];
	va_list arg;
	va_start(arg, format);
	_vsnprintf_s(buf, _TRUNCATE, format, arg);
	va_end(arg);
	g_message << buf << std::endl;

	/*
	// XPだけ別なのでOSのバージョンを取得
	OSVERSIONINFO OSver; OSver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
	GetVersionEx(&OSver);
	bool before_vista = (OSver.dwMajorVersion < 6);
	*/

	if(g_symbol_available) {
		enum { MAX_FRAMES = 20, MAX_NAME_LEN = 250 };
		void *stack[MAX_FRAMES];
		HANDLE processHandle = GetCurrentProcess();
		int frames = CaptureStackBackTrace( 0, MAX_FRAMES, stack, NULL );
		SYMBOL_INFO* symbol = (SYMBOL_INFO*)malloc(sizeof(SYMBOL_INFO) + MAX_NAME_LEN*sizeof(char));

		if(symbol != NULL) {
			symbol->MaxNameLen = MAX_NAME_LEN;
			symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

			g_message << "以下、スタックトレース" << std::endl;
			for(int i = 0; i < frames; ++i) {
				g_message << (i+1) << ": ";
				 if(SymFromAddr(processHandle, ( DWORD64 )( stack[ i ] ), 0, symbol )) {
					 g_message << symbol->Name <<
						 "() - 0x" << std::hex << symbol->Address << std::dec << std::endl;
				 }
				 else {
					 g_message << "スタックトレースの取得に失敗" << std::endl;
				 }
			 }
			free(symbol); symbol = NULL;
		}
	}
	else {
		g_message << "デバッグシンボルがないためスタックトレースを表示できません" << std::endl;
	}

	throw buf;
}

extern "C" utl::StringBuffer<char>* __stdcall get_internal_message_buffer();

void attach_neko() {
	// リロードする
	SymCleanup(GetCurrentProcess());
	g_symbol_available = (SymInitialize(GetCurrentProcess(), NULL, TRUE) != 0);

	g_message.attach(get_internal_message_buffer());
}

void detach_neko() {
	SymCleanup(GetCurrentProcess());
}

extern "C" int __stdcall get_message(char* buf, int len) {
	return g_message.getline(buf, len);
}
