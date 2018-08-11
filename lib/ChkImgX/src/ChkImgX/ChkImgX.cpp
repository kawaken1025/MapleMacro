/*--------------------------------------------------------------------------
* ChkImgX.dll メイン
* 
* created by Nekorabbit
*
* OpenCVを使っています。このプロジェクトファイルは環境変数$(OPENCV_HOME)を使って
* インクルードディレクトリやライブラリディレクトリを追加しているので、
* OPENCV_HOMEを環境変数に追加するか、追加のインクルードディレクトリ・ライブラリディレクトリ
* を変更するかして、OpenCVのファイルが見えるようにしてください。
* 
* このプロジェクトファイルは、依存ライブラリへのリンクをDebugビルドではダイナミックリンク
* Releaseビルドではスタティックリンクするようになっています。
*--------------------------------------------------------------------------*/
#include "stdafx.h"

#include "ChkImgX.hpp"
#include "tmatch_opencv.hpp"
#include "GDICapture.hpp"
#include "LightWnd.hpp"
#include "NekoAddon.hpp"
#include "search_base.hpp"

#include "comutil.h"

#ifdef _DEBUG
#define CV_EXT_STR "d.lib"
#else
#define CV_EXT_STR ".lib"
#endif


#pragma comment(lib, "opencv_core249" CV_EXT_STR)
#pragma comment(lib, "opencv_imgproc249" CV_EXT_STR)
//#pragma comment(lib, "opencv_highgui249" CV_EXT_STR)
//#pragma comment(lib, "opencv_ml249" CV_EXT_STR)
//#pragma comment(lib, "opencv_video249" CV_EXT_STR)
//#pragma comment(lib, "opencv_features2d249" CV_EXT_STR)
//#pragma comment(lib, "opencv_calib3d249" CV_EXT_STR)
//#pragma comment(lib, "opencv_objdetect249" CV_EXT_STR)
//#pragma comment(lib, "opencv_contrib249" CV_EXT_STR)
//#pragma comment(lib, "opencv_legacy249" CV_EXT_STR)
//#pragma comment(lib, "opencv_flann249" CV_EXT_STR)
#ifndef _DEBUG // スタティックリンクするときだけ
#pragma comment(lib, "zlib" CV_EXT_STR)
#endif

/*
	TODO:
	- ファイルの更新を検出する機構
	- 並列化する
*/

namespace chkimg {
	AppContext* g_app = NULL;
}

CRITICAL_SECTION g_global_lock;
bool g_initialized = false;
HANDLE g_module;

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

class CaptureScreen : public LightWnd {
public:
	CaptureScreen(std::string& message__, POINT* pt__)
		: background(NULL)
		, text_font(L"MS UI Gothic", 12)
		, text_brush(Gdiplus::Color(0,0,0))
		, labelRect(0,0,0,0)
		, success(false)
	{
		current.x = current.y = 100;
		chkimg::multi_byte_to_wchar(message__.c_str(), message);
		pt = pt__;

		windowRect = Gdiplus::RectF(
			GetSystemMetrics(SM_XVIRTUALSCREEN), GetSystemMetrics(SM_YVIRTUALSCREEN),
			GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN));
		SetBounds(windowRect.X, windowRect.Y, windowRect.Width, windowRect.Height);
		SetStyle(WS_POPUP|WS_VISIBLE|WS_SYSMENU);
		SetExStyle(WS_EX_TOPMOST|WS_EX_TOOLWINDOW);
	}

	~CaptureScreen() {
		if(background) { delete background ; background = NULL; }
	}

	virtual BOOL Show() {

		// スクリーンをキャプチャして白くする
		background = chkimg::captureScreen(NULL);
		chkimg::Bitmap bmp = background->data();
		uint8_t* scan0 = (uint8_t*)bmp.scan0;
		float a = 0.3f;
		for(int y = 0; y < bmp.height; ++y) {
			uint8_t* scanx = scan0 + y * bmp.stride;
			for(int x = 0; x < bmp.width; ++x) {
				scanx[3 * x + 0] = 255 - a * (255 - scanx[3 * x + 0]);
				scanx[3 * x + 1] = 255 - a * (255 - scanx[3 * x + 1]);
				scanx[3 * x + 2] = 255 - a * (255 - scanx[3 * x + 2]);
			}
		}
		background->unlock();
		success = false;

		return LightWnd::Show();
	}

	bool is_success() { return success; }

private:
	Gdiplus::RectF windowRect;
	chkimg::GDIBitmap* background;
	Gdiplus::Font text_font;
	Gdiplus::SolidBrush text_brush;
	Gdiplus::RectF labelRect;
	POINT current;
	std::wstring message;
	POINT *pt;
	bool success;

	virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam) {
		switch(msg) {
		case WM_CREATE:
			return 0;
		case WM_MOUSEMOVE:
			OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		case WM_LBUTTONUP:
			OnLButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		case WM_ERASEBKGND:
			return 1;
		case WM_PAINT:
			OnPaint();
			return 0;
		case WM_KEYDOWN:
			if(OnKeyDown(wParam)) {
				return 0;
			}
			break;
		}
		return LightWnd::WndProc(msg, wParam, lParam);
	}

	void OnMouseMove(int x, int y) {
		current.x = x; current.y = y;

		// 前後両方Invalidateする
		RECT rect1 = { labelRect.X, labelRect.Y, labelRect.X + labelRect.Width, labelRect.Y + labelRect.Height };
		InvalidateRect(GetHandle(), &rect1, FALSE);
		labelRect.X = current.x - labelRect.Width / 2;
		labelRect.Y = current.y - labelRect.Height;
		RECT rect2 = { labelRect.X, labelRect.Y, labelRect.X + labelRect.Width, labelRect.Y + labelRect.Height };
		InvalidateRect(GetHandle(), &rect2, FALSE);
	}

	void OnLButtonUp(int x, int y) {
		pt->x = x + windowRect.X; pt->y = y + windowRect.Y;
		success = true;
		Close();
	}

	void OnPaint() {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(GetHandle(), &ps);
		RECT paintRect = ps.rcPaint;
		{
			Gdiplus::Graphics g(hdc);
			g.DrawImage(background->ptr(), paintRect.left, paintRect.top, paintRect.left,
				paintRect.top, paintRect.right - paintRect.left, paintRect.bottom - paintRect.top,
				Gdiplus::UnitPixel);

			// 位置を計算
			g.MeasureString(message.c_str(), message.size(), &text_font, windowRect, &labelRect);
			
			labelRect.X = current.x - labelRect.Width / 2;
			labelRect.Y = current.y - labelRect.Height;
			Gdiplus::PointF pos(labelRect.X, labelRect.Y);

			// 書き込む
			g.DrawString(message.c_str(), message.size(), &text_font, pos, &text_brush);

		}
		EndPaint(GetHandle(), &ps);
	}

	bool OnKeyDown(WPARAM keyCode) {
		switch(keyCode) {
		case VK_ESCAPE:
		case VK_BACK:
		case VK_DELETE:
			Close();
			return true;
		}
		return false;
	}
};

//-------------------------------------------------------------//
// UWSC用エクスポート関数
//-------------------------------------------------------------//

extern "C" void __stdcall startup_chkimgx()
{
	using namespace chkimg;
	if(!g_initialized) {
		CriticalSection lock(g_global_lock);
		if(!g_initialized) {
			attach_neko();
			g_app = new AppContext();
			g_initialized = true;
		}
	}
}

extern "C" void __stdcall shutdown_chkimgx()
{
	using namespace chkimg;
	if(g_initialized) {
		LightWnd::UninitializeWndClass((HINSTANCE)g_module);
		delete g_app; g_app = NULL;
		detach_neko();
		g_initialized = false;
	}
}

extern "C" void __stdcall chkimgx_option(int dump, int backmode) {
	using namespace chkimg;
	g_app->dump_image = dump ? true : false;
	g_app->background_mode = backmode ? true : false;
}

extern "C" int __stdcall get_mouse_click(const char* message, POINT* pt) {
	CaptureScreen screen(std::string(message), pt);
	screen.Show();
	LightWnd::ApplicationLoop(&screen);
	return screen.is_success();
}

// startup を呼ばないで使う輩がいそうなので一応できるようにしておく
class TemporalInitializer {
	bool own;
public:
	TemporalInitializer() {
		using namespace chkimg;
		if(g_app == NULL) {
			own = true;
			g_app = new AppContext();
		}
		else {
			own = false;
		}
	}
	~TemporalInitializer() {
		using namespace chkimg;
		if(own) {
			delete g_app;
		}
	}
};

void internal_match(
	HWND h_wnd,
	const char* filename,
	RECT* rect,
	double window_scale,
	double matching_scale, 
	double diff_limit,
	int order, // 0: スコア順, 1: 位置順
	std::vector<chkimg::SearchResult>& allResult,
	int* limit)
{
	using namespace chkimg;
	TemporalInitializer ti_;
	win_int64_t freq, before, after;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&before);

	double window_to_matching = matching_scale / window_scale;
	RECT wrect = scale_rect(rect, window_scale);
	ImageCacheEntry img(captureScreen(h_wnd, &wrect, 1.0, g_app->background_mode), window_to_matching, -1);
	ImageCache& images = g_app->loadImage(filename, matching_scale);
	if(g_app->dump_image) {
		g_app->enc.saveBitmapAsPNG(img.data()->ptr(), "capture.png");
		for(ImageCacheEntry* entry : images) {
			utl::StringBuffer<char> string_buf;
			string_buf << "tmpl-" << entry->number() << ".png";
			std::string str; string_buf >> str;
			g_app->enc.saveBitmapAsPNG(entry->data()->ptr(), str.c_str());
		}
	}
	// テンプレートマッチを実行
	MatchTemplateRGB mtopencv; mtopencv.init(img.data()->data());
	for(int i = 0; i < int(images.size()); ++i) {
		std::vector<SearchResult>& result = mtopencv.search(images[i]->data()->data(), diff_limit);
		int image_number = images[i]->number();
		for(int c = 0; c < int(result.size()); ++c) {
			result[c].number = image_number;
		}
		allResult.insert(allResult.end(), result.begin(), result.end());
	}
	processResult(allResult, &wrect, images[0]->originalSize(), matching_scale, int(images.size()), order);
	
	QueryPerformanceCounter(&after);
	*limit = int((after - before) * 1000 / freq);
}

void internal_match(
	HWND h_wnd,
	const char* filename,
	RECT* rect,
	double window_scale,
	double matching_scale,
	int color,
	double diff_limit,
	int order, // 0: スコア順, 1: 位置順
	std::vector<chkimg::SearchResult>& allResult,
	int* limit)
{
	using namespace chkimg;
	TemporalInitializer ti_;
	win_int64_t freq, before, after;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&before);
	
	double window_to_matching = matching_scale / window_scale;
	RECT wrect = scale_rect(rect, window_scale);
	ImageCacheEntry img(captureScreen(h_wnd, &wrect, 1.0, g_app->background_mode), window_to_matching, -1);
	Bitmap grayImage = img.grayImage(color);
	ImageCache& images = g_app->loadImage(filename, matching_scale);
	if(g_app->dump_image) {
		g_app->enc.saveBitmapAsPNG(img.data()->ptr(), "capture.png");
		g_app->enc.saveBitmapAsPNG(img.grayRGBImage(color)->ptr(), "capture-bin.png");
		for(ImageCacheEntry* entry : images) {
			utl::StringBuffer<char> string_buf;
			string_buf << "tmpl-" << entry->number() << ".png";
			std::string str; string_buf >> str;
			g_app->enc.saveBitmapAsPNG(entry->grayRGBImage(color)->ptr(), str.c_str());
		}
	}
	// テンプレートマッチを実行
	MatchTemplateGray matcher; matcher.init(img.grayImage(color));
	for(int i = 0; i < int(images.size()); ++i) {
		std::vector<SearchResult>& result = matcher.search(images[i]->grayImage(color), diff_limit);
		int image_number = images[i]->number();
		for(int c = 0; c < int(result.size()); ++c) {
			result[c].number = image_number;
		}
		allResult.insert(allResult.end(), result.begin(), result.end());
	}
	processResult(allResult, &wrect, images[0]->originalSize(), matching_scale, int(images.size()), order);
	
	QueryPerformanceCounter(&after);
	*limit = int((after - before) * 1000 / freq);
}

extern "C" int __stdcall chkimgx_generic(
	HWND h_wnd,
	const char* filename,
	RECT* rect,
	double window_scale,
	double matching_scale,
	int color,
	double diff_limit,
	int* x,
	int* y,
	int* match_number,
	double* score,
	int max_points,
	int order,
	int* limit)
{
	using namespace chkimg;
#ifdef NDEBUG
	try {
#endif
		if(filename == NULL || x == NULL || y == NULL || match_number == NULL || score == NULL || limit == NULL) {
			throw_exception("パラメータNULLは許可されていません");
		}
		check_parameters(rect, window_scale, matching_scale, diff_limit, max_points);
		std::vector<chkimg::SearchResult> allResult;
		if(color < 0 || color > 0xFFFFFF) {
			internal_match(h_wnd, filename, rect, window_scale, matching_scale,
				diff_limit, order, allResult, limit);
		}
		else {
			internal_match(h_wnd, filename, rect, window_scale, matching_scale, color,
				diff_limit, order, allResult, limit);
		}
		int ret = storeResult(allResult, x, y, match_number, score, max_points);
		return ret;
#ifdef NDEBUG
	}
	catch (const char*) {
		// C++例外はDLL境界を越えられないので、構造化例外に変換する
		RaiseException(0, 0, 0, NULL);
	}
	return 0;
#endif
}

extern "C" void __stdcall imagesize(const char* filename, POINT* point)
{
	using namespace chkimg;
#ifdef NDEBUG
	try {
#endif
		TemporalInitializer ti_;
		*point = g_app->imageSize(filename);
#ifdef NDEBUG
	}
	catch (const char*) {
		// C++例外はDLL境界を越えられないので、構造化例外に変換する
		RaiseException(0, 0, 0, NULL);
	}
#endif
}

#ifndef CHKIMGX
extern "C" void __stdcall encrypt_file(const char* srcfile, const char* dstfile) {
#ifdef NDEBUG
	try {
#endif
		const HANDLE srcFile = CreateFile(srcfile, GENERIC_READ, 0,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(srcFile == INVALID_HANDLE_VALUE)
			throw_exception("ファイルが見つかりません: %s", srcfile);
		const DWORD dwFileSize = GetFileSize(srcFile, NULL);
		void* data = malloc(dwFileSize);
		DWORD dwLoadSize;
		ReadFile(srcFile, data, dwFileSize, &dwLoadSize, NULL);
		CloseHandle(srcFile);

		chkimg::xorEncrypt(data, dwLoadSize);
	
		const HANDLE dstFile = CreateFile(dstfile, GENERIC_WRITE, 0,
			NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(srcFile == INVALID_HANDLE_VALUE)
			throw_exception("ファイルが開けません: %s", dstfile);
		DWORD dwBytesWritten;
		WriteFile(dstFile, data, dwLoadSize, &dwBytesWritten, NULL);
		CloseHandle(dstFile);
#ifdef NDEBUG
	}
	catch (const char*) {
		// C++例外はDLL境界を越えられないので、構造化例外に変換する
		RaiseException(0, 0, 0, NULL);
	}
#endif
}
#endif // #ifndef CHKIMGX

extern "C" int __stdcall get_screen_rect(RECT* rect) {
	rect->left = GetSystemMetrics(SM_XVIRTUALSCREEN);
	rect->top = GetSystemMetrics(SM_YVIRTUALSCREEN);
	rect->right = GetSystemMetrics(SM_CXVIRTUALSCREEN) + rect->left;
	rect->bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN) + rect->top;
	return 0;
}

#ifndef _CONSOLE

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

#else

#include "debug_main.hpp"

#endif

