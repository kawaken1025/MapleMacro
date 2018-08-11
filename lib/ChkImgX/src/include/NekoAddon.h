/*--------------------------------------------------------------------------
* ChkImgEx.dll ÉÅÉCÉì
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#pragma once

#include <vld.h> 
#include "string_buffer.h"

void throw_exception(const char* format, ...);
extern utl::SharedStringBuffer<char> g_message;
