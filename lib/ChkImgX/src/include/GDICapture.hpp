/*--------------------------------------------------------------------------
* GDI+のラッパー
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#pragma once

#include <objidl.h>
#include <gdiplus.h>
#include "GDICapture.h"

#undef min
#undef max

namespace chkimg {

void multi_byte_to_wchar(
	const std::string& value, std::wstring& out
) {
	int wideCharLen = ::MultiByteToWideChar(CP_ACP, 0, value.c_str(), -1, NULL, 0);
	out.resize(wideCharLen);
	out.resize(::MultiByteToWideChar(CP_ACP, 0, value.c_str(), -1, &out[0], wideCharLen));
}

void multi_byte_to_wchar(
	const char* value, std::wstring& out
) {
	int wideCharLen = ::MultiByteToWideChar(CP_ACP, 0, value, -1, NULL, 0);
	out.resize(wideCharLen);
	out.resize(::MultiByteToWideChar(CP_ACP, 0, value, -1, &out[0], wideCharLen));
}

//////////////////////////////////////////////////////////////////////////
// Encoder
//////////////////////////////////////////////////////////////////////////

GDIEncoder::GDIEncoder()
{
	if(initEncoderClsid() == false)
		throw "エンコーダが見つかりません";
}

// 補助関数
void GDIEncoder::saveBitmapAsBMP(Gdiplus::Bitmap* bitmap, const char* filename_) const {
	std::wstring filename; multi_byte_to_wchar(filename_, filename);
	bitmap->Save(filename.c_str(), &bmpEncoder, NULL);
}
void GDIEncoder::saveBitmapAsPNG(Gdiplus::Bitmap* bitmap, const char* filename_) const {
	std::wstring filename; multi_byte_to_wchar(filename_, filename);
	bitmap->Save(filename.c_str(), &pngEncoder, NULL);
}
void GDIEncoder::saveBitmapAsJPEG(Gdiplus::Bitmap* bitmap, const char* filename_) const {
	std::wstring filename; multi_byte_to_wchar(filename_, filename);
	bitmap->Save(filename.c_str(), &jpegEncoder, NULL);
}

bool GDIEncoder::initEncoderClsid() {
	UINT  num = 0, size = 0;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return false;

	Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)malloc(size);
	if (pImageCodecInfo == NULL)
		return false;  // Failure

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	int numEncoders = 0;
	for(UINT j = 0; j < num; ++j) {
		if (wcscmp(pImageCodecInfo[j].MimeType, L"image/bmp") == 0) {
			bmpEncoder = pImageCodecInfo[j].Clsid;
			++numEncoders;
		}
		else if (wcscmp(pImageCodecInfo[j].MimeType, L"image/png") == 0) {
			pngEncoder = pImageCodecInfo[j].Clsid;
			++numEncoders;
		}
		else if (wcscmp(pImageCodecInfo[j].MimeType, L"image/jpeg") == 0) {
			jpegEncoder = pImageCodecInfo[j].Clsid;
			++numEncoders;
		}
	}

	free(pImageCodecInfo);
	return numEncoders == 3;
}

//////////////////////////////////////////////////////////////////////////
// 画像ファイル暗号化
//////////////////////////////////////////////////////////////////////////

static DWORD g_encrypt_key = 0xE8F29FACUL;

void xorEncrypt(void* data, int len) {
	DWORD* ptr = (DWORD*)data;
	for(int i = 0; i < (len/sizeof(DWORD)); ++i) {
		ptr[i] ^= g_encrypt_key;
	}
}

//////////////////////////////////////////////////////////////////////////
// 補助関数
//////////////////////////////////////////////////////////////////////////

void ForceIntoBoundingBox(RECT* rect,
						  int bleft, int btop, int bw, int bh)
{
	rect->top = std::max<int>(rect->top, btop);
	rect->left = std::max<int>(rect->left, bleft);
	rect->right = std::min<int>(rect->right, btop + bw);
	rect->bottom = std::min<int>(rect->bottom, btop + bh);
}

// 画像を読み込んだメモリブロックのIStreamを作成
IStream * createFileStream(const char *filepath, bool decrypt)
{
	// 画像ファイルオープン
	const HANDLE hFile = CreateFile(filepath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		throw_exception("ファイルが見つかりません: %s", filepath);

	// ファイルサイズ取得
	const DWORD dwFileSize = GetFileSize(hFile, NULL);
	// 画像ファイルデータ格納用メモリブロック確保
	const HGLOBAL hBuf = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
	if(hBuf == NULL)
		throw_exception("GlobalAllocに失敗");
		
	// メモリブロックをロックしアドレスを取得
	const LPVOID lpBuf = GlobalLock(hBuf);
	// 画像ファイルのデータをメモリブロックに読み込む
	DWORD dwLoadSize;
	ReadFile(hFile, lpBuf, dwFileSize, &dwLoadSize, NULL);
	if(dwFileSize != dwLoadSize)
		throw_exception("ReadFileに失敗");
	CloseHandle(hFile);
	// メモリブロックのロック解除
	GlobalUnlock(hBuf);

	// 必要なら復号
	if(decrypt) {
		xorEncrypt(lpBuf, dwLoadSize);
	}

	// メモリブロックからIStreamを作成
	IStream * isFile;
	HRESULT hr = CreateStreamOnHGlobal(hBuf, TRUE, &isFile);
	if(FAILED(hr) || isFile == NULL)
		throw_exception("CreateStreamOnHGlobalに失敗");
	// IStreamを返す
	return isFile;
}

// 画像を読み込んだメモリブロックのIStreamを作成
IStream * createResourceStream(HMODULE module, WORD id)
{
	HRSRC hRsc = FindResource(module, MAKEINTRESOURCE(id), "PNG");
	if(hRsc == NULL)
		throw_exception("リソースが見つかりません");
	
	// まぁ、実際は何もしない、ただの取得関数なんだけどね
	DWORD dwFileSize = SizeofResource(module, hRsc);
	if(dwFileSize == 0)
		throw_exception("リソースのサイズ取得に失敗");
	
	// まぁ、実際は何もしない、ただの取得関数なんだけどね
	HGLOBAL hData = LoadResource(module, hRsc);
	if(hData == NULL)
		throw_exception("リソースのロードに失敗");
	
	// まぁ、実際は何もしない、ただの取得関数なんだけどね
	LPVOID pData = LockResource(hData);
	if(pData == NULL)
		throw_exception("リソースのロックに失敗");

	// 画像ファイルデータ格納用メモリブロック確保
	const HGLOBAL hBuf = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
	if(hBuf == NULL)
		throw_exception("GlobalAllocに失敗");
		
	// メモリブロックをロックしアドレスを取得
	const LPVOID lpBuf = GlobalLock(hBuf);
	// 画像ファイルのデータをメモリブロックに読み込む
	memcpy(lpBuf, pData, dwFileSize);
	// メモリブロックのロック解除
	GlobalUnlock(hBuf);

	// メモリブロックからIStreamを作成
	IStream * isFile;
	HRESULT hr = CreateStreamOnHGlobal(hBuf, TRUE, &isFile);
	if(FAILED(hr) || isFile == NULL)
		throw_exception("CreateStreamOnHGlobalに失敗");
	// IStreamを返す
	return isFile;
}

GDIBitmap* copyBitmap(HDC winDC, int x, int y, int w, int h, double scale) {
	int dst_w = w * scale;
	int dst_h = h * scale;
	
	// コピー先のビットマップを作成
	GDIBitmap* bmp = new GDIBitmap(dst_w, dst_h);
	try {
		//Graphicsの作成
		Gdiplus::Graphics g(bmp->ptr());
		//Graphicsのデバイスコンテキストを取得
		HDC hDC = g.GetHDC();
		//Bitmapに画像をコピーする
		if(scale == 1.0) {
			if(BitBlt(hDC, 0, 0, w, h, winDC, x, y, SRCCOPY) == 0)
				throw_exception("BitBltに失敗");
		}
		else {
			if(StretchBlt(hDC, 0, 0, dst_w, dst_h, winDC, x, y, w, h, SRCCOPY) == 0)
				throw_exception("StretchBltに失敗");
		}
		//解放
		g.ReleaseHDC(hDC);
	}
	catch(const char* str) {
		delete bmp; bmp = NULL;
		throw str;
	}

	return bmp;
}

// 関数から帰ると
// 実際にキャプチャした座標がrectに入る
GDIBitmap* captureScreen(HWND hWnd, RECT* rect, double scale, bool backgroud_mode) {
	// デスクトップスクリーンのデバイスコンテキストを作成
	HDC winDC;
	if(hWnd != NULL) {
		// 特定ウィンドウ
		winDC = GetWindowDC(hWnd);
		if(winDC == NULL)
				throw_exception("GetWindowDCに失敗");
	}
	else {
		// デスクトップ
		winDC = GetDC(NULL);
		if(winDC == NULL)
				throw_exception("GetDCに失敗");
	}
 
	// 範囲をウィンドウ内に収める
	RECT wndRect;
	if(hWnd != NULL) {
		GetWindowRect(hWnd, &wndRect);
		ForceIntoBoundingBox(rect,
			0, 0, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top);
	}
	else {
		ForceIntoBoundingBox(rect,
			GetSystemMetrics(SM_XVIRTUALSCREEN), GetSystemMetrics(SM_YVIRTUALSCREEN),
			GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN));
	}
	int x = rect->left, y = rect->top;
	int w = rect->right - rect->left, h = rect->bottom - rect->top;
	
	GDIBitmap* bmp = NULL;
	GDIBitmap* tmp = NULL;

	if(hWnd != NULL && !backgroud_mode) {
		// 直接取れない場合があるのでPrintWindowで取っておく
		int win_w = wndRect.right - wndRect.left;
		int win_h = wndRect.bottom - wndRect.top;
		tmp = new GDIBitmap(win_w, win_h);
		try {
			//Graphicsの作成
			Gdiplus::Graphics g(tmp->ptr());
			//Graphicsのデバイスコンテキストを取得
			HDC hDC = g.GetHDC();
			if(PrintWindow(hWnd, hDC, 0) == 0)
				throw_exception("PrintWindowに失敗");

			if(x == 0 && y == 0 && w == win_w && h == win_h && scale == 1.0) {
				// ウィンドウ全体をそのままの大きさなのでコピーしない
				bmp = tmp;
			}
			else {
				// PrintWindowしたbitmapからコピー
				bmp = copyBitmap(hDC, x, y, w, h, scale);
			}
			//解放
			g.ReleaseHDC(hDC);
		}
		catch(const char* str) {
			delete tmp; tmp = NULL;
			throw str;
		}
	}
	else {
		// 直接コピー
		bmp = copyBitmap(winDC, x, y, w, h, scale);
	}

	// 解放
	ReleaseDC(hWnd, winDC);
	if(tmp != NULL && tmp != bmp) {
		delete tmp; tmp = NULL;
	}

	return bmp;
}

GDIBitmap* captureScreen(HWND hWnd, double scale) {
	RECT rect;
	if(hWnd == NULL) {
		// デスクトップ全体をキャプチャ
		rect.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
		rect.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
		rect.right = rect.left + GetSystemMetrics(SM_CXVIRTUALSCREEN);
		rect.bottom = rect.top + GetSystemMetrics(SM_CYVIRTUALSCREEN);
	}
	else {
		GetWindowRect(hWnd, &rect);
		rect.right -= rect.left; rect.left = 0;
		rect.bottom -= rect.top; rect.top = 0;
	}
	return captureScreen(hWnd, &rect, scale);
}

} // chkimg
