
#pragma once

#include <Windows.h>
#include <string>

class LightWnd
{
public:
	LightWnd();
	virtual ~LightWnd();

	
	static void InitializeWndClass(HINSTANCE hInst = NULL)
	{
		WNDCLASSEX myProg = {};
		myProg.cbSize = sizeof(WNDCLASSEX);
		myProg.style = CS_HREDRAW | CS_VREDRAW;
		myProg.lpfnWndProc = RealWndProc;
		myProg.cbClsExtra = 0;
		myProg.cbWndExtra = sizeof(void*);// このオブジェクトへのポインタを格納するため
		myProg.hInstance = hInst ? hInst : GetModuleHandle(NULL);
		myProg.hIcon = NULL;
		myProg.hCursor = LoadCursor(NULL, IDC_ARROW);
		myProg.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
		myProg.lpszMenuName = NULL;
		myProg.lpszClassName = WndClassName;
		if( !RegisterClassEx(&myProg) ){
		// 終了時に削除できないことがあるのでエラーにはしないことにする
		//	throw "RegisterClassExに失敗";
		}
		LightWnd::Initialized = TRUE;
	}
	// DLLの場合、自動で登録解除されないので明示的に行う
	static void UninitializeWndClass(HINSTANCE hInst = NULL) {
		if(LightWnd::Initialized) {
			UnregisterClass(WndClassName, hInst ? hInst : GetModuleHandle(NULL));
			LightWnd::Initialized = FALSE;
		}
	}

	void SetStyle(DWORD style) {
		m_dwStyle = style;
	}
	void SetExStyle(DWORD exStyle) {
		m_dwExStyle = exStyle;
	}
	void SetCaption(std::string text) {
		m_Caption = text;
	}
	void SetBounds(int x, int y, int w, int h) {
		WndRect.X = x;
		WndRect.Y = y;
		WndRect.W = w;
		WndRect.H = h;
	}
	HWND GetHandle();
	virtual BOOL Show();
	BOOL Close();
	
	int GetWidth() { return WndRect.W; }
	int GetHeight() { return WndRect.H; }
	
	static void PeekMessages(LightWnd* pMainWnd);
	static size_t ApplicationLoop(LightWnd* pMainWnd);
protected:
	HWND m_hWnd;
	std::string m_Caption;
	BOOL m_bVisible;

	BOOL CreateHandle();
	virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
private:
	static LPCSTR WndClassName;
	static BOOL Initialized;
	__declspec( thread ) static LightWnd* CurrentWnd;

	DWORD m_dwExStyle, m_dwStyle;
	struct {
		DWORD X, Y, W, H;
	} WndRect;

	static LRESULT CALLBACK RealWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};


