// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください。

#include <objidl.h>
#include <gdiplus.h>

#include <locale.h>

#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"comsuppwd.lib")

#include <imagehlp.h>
#pragma comment( lib, "imagehlp.lib" )

#include <Windowsx.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <commctrl.h>

void throw_exception(const char* format, ...);

#ifndef NDEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG(s) s
#else
#define DEBUG(s)
#endif
