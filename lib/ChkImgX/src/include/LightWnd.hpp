
#pragma once

#include "LightWnd.h"

LPCSTR LightWnd::WndClassName =  "LightWnd_WindowClass_" LWND_NAME_EXT;
BOOL LightWnd::Initialized = FALSE;
LightWnd* LightWnd::CurrentWnd = NULL;

LightWnd::LightWnd() :
	m_Caption("LightWnd")
{
	if(Initialized == false) {
		InitializeWndClass();
	}
	m_hWnd = NULL;
	m_bVisible = FALSE;
	m_dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;	//ウィンドウスタイル
	m_dwExStyle = 0;	// 拡張ウィンドウスタイル
	WndRect.X = CW_USEDEFAULT;
	WndRect.Y = CW_USEDEFAULT;
	WndRect.W = CW_USEDEFAULT;
	WndRect.H = CW_USEDEFAULT;
}

LightWnd::~LightWnd()
{
	Close();
}

HWND LightWnd::GetHandle()
{
	if( m_hWnd == NULL ){
		CreateHandle();
	}
	return m_hWnd;
}

BOOL LightWnd::Show()
{
	BOOL bOK = TRUE;
	if( m_bVisible == FALSE ){
		if( m_hWnd == NULL ){
			bOK = FALSE;
			CreateHandle();
		}
		if( m_hWnd ){
			ShowWindow(m_hWnd, SW_SHOWDEFAULT);
			UpdateWindow(m_hWnd);
			m_bVisible = TRUE;
			bOK = TRUE;
		}
	}
	return bOK;
}

BOOL LightWnd::CreateHandle()
{
	BOOL bOK = FALSE;
	if( Initialized ){
		CurrentWnd = this;
		m_hWnd = CreateWindowEx(
			m_dwExStyle,		// 拡張ウィンドウスタイル
			WndClassName,	//クラス名
			m_Caption.c_str(),	//ウィンドウの名前
			m_dwStyle,			//ウィンドウスタイル
			WndRect.X,			//Ｘ座標
			WndRect.Y,			//Ｙ座標
			WndRect.W,			//ウィンドウの横幅
			WndRect.H,			//ウィンドウの高さ
			NULL,				//親ウィンドウハンドル（親を作るときはNULL）
			NULL,				//メニューハンドル、クラスメニューの時はNULL
			NULL,				//インスタンスハンドル
			NULL);				//ウィンドウ作成データ
		if( m_hWnd != NULL ){
			SetWindowLongPtr(m_hWnd, 0, (ULONG_PTR)this);
			bOK = TRUE;
		}
		CurrentWnd = NULL;
	}
	return bOK;
}

BOOL LightWnd::Close()
{
	if( m_hWnd ){
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
	return TRUE;
}

void LightWnd::PeekMessages(LightWnd* pMainWnd)
{
	MSG msg;
	while (true) {
		if(!PeekMessage(&msg, pMainWnd->m_hWnd, 0, 0, PM_REMOVE)) {
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

size_t LightWnd::ApplicationLoop(LightWnd* pMainWnd)
{
	MSG msg;
	while (true) {
		BOOL bRet = GetMessage(&msg, NULL, 0, 0);
		if( bRet == -1 ){
			return 0;
		}
		else if( bRet == 0 ){
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT LightWnd::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg){
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(m_hWnd, msg, wParam, lParam);
	}
	return 0L;
}

LRESULT CALLBACK LightWnd::RealWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LightWnd* pThis = (LightWnd*)GetWindowLongPtr(hWnd, 0);
	if( pThis ){
		_ASSERT( pThis->m_hWnd == hWnd );
		return pThis->WndProc(msg, wParam, lParam);
	}
	else {
		LightWnd::CurrentWnd->m_hWnd = hWnd;
		return LightWnd::CurrentWnd->WndProc(msg, wParam, lParam);
	}
	return 0L;
}
