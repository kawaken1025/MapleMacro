/*--------------------------------------------------------------------------
* LARGE_INTEGERのラッパー
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#pragma once

#ifndef WIN_INT64_TYPE_H__
#define WIN_INT64_TYPE_H__

#include <Windows.h>

class win_int64_pointer_t;

class win_int64_t
{
private:
	LARGE_INTEGER data;
public:
	win_int64_t() { }
	win_int64_t(const __int64 qw) { data.QuadPart = qw; }
	win_int64_t(const DWORD high, const DWORD low)
	{
		data.HighPart = high;
		data.LowPart = low;
	}
	win_int64_t(const LARGE_INTEGER li) { data.QuadPart = li.QuadPart; }
	// キャスト
	operator __int64() { return data.QuadPart; }
	operator LARGE_INTEGER(){ return data; }
	win_int64_pointer_t operator&();
	// 単項演算子
	win_int64_t& operator=(const __int64 qw)
	{
		data.QuadPart = qw;
		return *this;
	}
	win_int64_t operator~(){ return win_int64_t(~data.QuadPart); }
	win_int64_t operator!() { return win_int64_t(!data.QuadPart); }
	win_int64_t& operator++()
	{ 
		++data.QuadPart;
		return *this;
	}
	win_int64_t& operator--()
	{
		--data.QuadPart;
		return *this;
	}
	win_int64_t operator++(int)
	{
		win_int64_t old(data.QuadPart++);
		return old;
	}
	win_int64_t operator--(int)
	{
		win_int64_t old(data.QuadPart--);
		return old;
	}
	void operator+=(const __int64 other){ data.QuadPart += other; }
	void operator-=(const __int64 other) { data.QuadPart -= other; }
	void operator*=(const __int64 other) { data.QuadPart *= other; }
	void operator/=(const __int64 other) { data.QuadPart /= other; }
	// ２項演算子
	/*
	__int64 operator + (const __int64 other) const { return data.QuadPart + other; }
	__int64 operator - (const __int64 other) const { return data.QuadPart - other; }
	__int64 operator * (const __int64 other) const { return data.QuadPart * other; }
	__int64 operator / (const __int64 other) const { return data.QuadPart / other; }
	*/
	// メソッド
	DWORD HighPart(){ return data.HighPart; }
	const DWORD HighPart() const { return data.HighPart; }
	DWORD LowPart(){ return data.LowPart; }
	const DWORD LowPart() const { return data.LowPart; }

	friend win_int64_pointer_t;
};

// ポインタも処理したいので定義
class win_int64_pointer_t
{
private:
	win_int64_t* ptr;
public:
	win_int64_pointer_t(win_int64_t* p) : ptr(p) { }
	// キャスト
	operator __int64*() { return &ptr->data.QuadPart; }
	operator LARGE_INTEGER*() { return &ptr->data; }
	operator win_int64_t*() { return ptr; }
};

inline win_int64_pointer_t win_int64_t::operator&() { return win_int64_pointer_t(this); }


#endif // #ifndef WIN_INT64_TYPE_H__
