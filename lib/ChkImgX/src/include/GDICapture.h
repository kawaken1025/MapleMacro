/*--------------------------------------------------------------------------
* GDI+のラッパー
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#pragma once

#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include "search_base.h"

namespace chkimg {

// 画像を読み込んだメモリブロックのIStreamを作成
IStream * createFileStream(const char *filepath, bool decrypt);

void ForceIntoBoundingBox(int& x, int& y, int& w, int& h,
						  int bx, int by, int bw, int bh);

class GDIEncoder {
public:
	GDIEncoder();
	// 補助関数
	void saveBitmapAsBMP(Gdiplus::Bitmap* bitmap, const char* filename) const;
	void saveBitmapAsPNG(Gdiplus::Bitmap* bitmap, const char* filename) const;
	void saveBitmapAsJPEG(Gdiplus::Bitmap* bitmap, const char* filename) const;

private:
	CLSID bmpEncoder;
	CLSID pngEncoder;
	CLSID jpegEncoder;

	bool initEncoderClsid();
};

class GDIBitmap {
	// 初期化・破棄をGdiplusのオブジェクト同じようにコンストラクタ・デストラクタで行うため
	class WappedBitmapHandle {
		HBITMAP hBitmap;
	public:
		WappedBitmapHandle()
			: hBitmap(NULL)
		{ }
		WappedBitmapHandle(HDC hDC, int w, int h)
			: hBitmap(CreateCompatibleBitmap(hDC, w, h))
		{
			if(hBitmap == NULL)
				throw_exception("CreateCompatibleBitmapに失敗");
		}
		~WappedBitmapHandle() {
			if(hBitmap) { DeleteObject(hBitmap); hBitmap = NULL; }
		}
		HBITMAP operator()() { return hBitmap; }
	};
	class WappedIStream {
		IStream* refStream;
	public:
		WappedIStream()
			: refStream(NULL)
		{ }
		WappedIStream(const char* imgpath, bool decrypt)
			: refStream(chkimg::createFileStream(imgpath, decrypt))
		{ }
		~WappedIStream() {
			if(refStream) { refStream->Release(); refStream = NULL; }
		}
		IStream* operator()() { return refStream; }
	};

public:
	GDIBitmap(HDC hDC, int w, int h)
		: hBitmap(hDC, w, h)
		, refStream()
		, gdiBitmap(hBitmap(), (HPALETTE)GetStockObject(DEFAULT_PALETTE))
		, locked(false)
	{ }
	GDIBitmap(int w, int h)
		: hBitmap()
		, refStream()
		, gdiBitmap(w, h, PixelFormat24bppRGB)
		, locked(false)
	{ }
	GDIBitmap(const char* imgpath, bool decrypt)
		: hBitmap()
		, refStream(imgpath, decrypt)
		, gdiBitmap(refStream())
		, locked(false)
	{
	}
	void lock() {
		if(locked == false) {
			locked = true;
			int imgWidth = gdiBitmap.GetWidth();
			int imgHeight = gdiBitmap.GetHeight();
			Gdiplus::Rect imgRect(0, 0, imgWidth, imgHeight);
			if(gdiBitmap.LockBits(&imgRect, Gdiplus::ImageLockModeRead, PixelFormat24bppRGB, &gitBitmapData) != Gdiplus::Ok)
					throw_exception("LockBitsに失敗");
		}
	}
	void unlock() {
		if(locked == true) {
			locked = false;
			if(gdiBitmap.UnlockBits(&gitBitmapData) != Gdiplus::Ok)
					throw_exception("UnlockBitsに失敗");
		}
	}
	~GDIBitmap() { unlock(); }
	Gdiplus::Bitmap& operator()() { return gdiBitmap; }
	Gdiplus::Bitmap* ptr() { return &gdiBitmap; }
	HBITMAP HBITMAP() { return hBitmap(); }
	Bitmap data() {
		lock();
		Bitmap img = { gitBitmapData.Width, gitBitmapData.Height, gitBitmapData.Stride, gitBitmapData.Scan0 };
		return img;
	}
private:
	// 初期化・破棄順
	WappedBitmapHandle hBitmap;
	WappedIStream refStream;
	Gdiplus::Bitmap gdiBitmap;
	Gdiplus::BitmapData gitBitmapData;
	bool locked;
};

GDIBitmap* captureScreen(HWND hWnd, RECT* rect, double scale = 1.0, bool backgroud_mode = false);
GDIBitmap* captureScreen(HWND hWnd, double scale = 1.0); // ウィンドウ全体をキャプチャ

} // chkimg
