#pragma once

#include <windows.h>

#define USE_CONSOLE					1

enum CONSOLE_TXT_COLOR {
	TXT_BLACK = 0 ,
	TXT_DARK_BLUE = FOREGROUND_BLUE ,
	TXT_DARK_GREEN = FOREGROUND_GREEN ,
	TXT_DARK_RED = FOREGROUND_RED ,
	TXT_LIGHT_BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE ,
	TXT_LIGHT_GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN ,
	TXT_LIGHT_RED = FOREGROUND_INTENSITY | FOREGROUND_RED ,
	TXT_DEFAULT = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED ,

	// background
	BG_DARK_BLUE = BACKGROUND_BLUE ,
	BG_DARK_GREEN = BACKGROUND_GREEN ,
	BG_DARK_RED = BACKGROUND_RED ,
	BG_LIGHT_BLUE = BACKGROUND_INTENSITY | BACKGROUND_BLUE ,
	BG_LIGHT_GREEN = BACKGROUND_INTENSITY | BACKGROUND_GREEN ,
	BG_LIGHT_RED = BACKGROUND_INTENSITY | BACKGROUND_RED ,
};

enum eGPU_error_level {
	eGPU_error_information ,
	eGPU_error_warning ,
	eGPU_error_fatal_error
};

void CONSOLE_debug_init ( );

unsigned short CONSOLE_get_current_color ( void );

void CONSOLE_change_color ( unsigned short color );

void CONSOLE_printf_gpu_error ( eGPU_error_level err_level , const char *fmt , ... );
void CONSOLE_wprintf_gpu_error ( eGPU_error_level err_level , const wchar_t *fmt , ... );

