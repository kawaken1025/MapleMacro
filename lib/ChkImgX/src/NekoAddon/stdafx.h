// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include <Windows.h>
#include <commctrl.h>

#include "NekoAddon.h"

#ifndef NDEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG(s) s
#else
#define DEBUG(s)
#endif
