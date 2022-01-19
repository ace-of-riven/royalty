#include "console.h"

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#define CONSOLE_PRINTF_HIDE(i)			va_list args; \
						va_start ( args , fmt ); \
						vfprintf ( i , fmt , args ); \
						va_end ( args );

#define CONSOLE_WPRINTF_HIDE(i)			va_list args; \
						va_start ( args , fmt ); \
						vfwprintf ( i , fmt , args ); \
						va_end ( args );

unsigned short CONSOLE_get_current_color ( void ) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	if ( !GetConsoleScreenBufferInfo ( GetStdHandle ( STD_OUTPUT_HANDLE ) , &info ) )
		return 0;
	return info.wAttributes;
}

void CONSOLE_change_color ( unsigned short color ) {
	HANDLE hSTDOUT = GetStdHandle ( STD_OUTPUT_HANDLE );
	if ( hSTDOUT )
		SetConsoleTextAttribute ( hSTDOUT , color );
}

static unsigned short CONSOLE_color_from_gpu_error_level ( eGPU_error_level err_level ) {
	switch ( err_level ) {
		case eGPU_error_level::eGPU_error_information:
			return CONSOLE_TXT_COLOR::TXT_LIGHT_RED | CONSOLE_TXT_COLOR::TXT_LIGHT_BLUE | CONSOLE_TXT_COLOR::TXT_LIGHT_GREEN;	// white
		case eGPU_error_level::eGPU_error_warning:
			return CONSOLE_TXT_COLOR::TXT_LIGHT_RED | CONSOLE_TXT_COLOR::TXT_LIGHT_GREEN;						// yellow
		case eGPU_error_level::eGPU_error_fatal_error:
			return CONSOLE_TXT_COLOR::TXT_LIGHT_RED;										// red
	}
	return 0;
}

void CONSOLE_printf_gpu_error ( eGPU_error_level err_level , const char *fmt , ... ) {
	unsigned short col = CONSOLE_get_current_color ( );
	CONSOLE_change_color ( CONSOLE_color_from_gpu_error_level ( err_level ) );
	CONSOLE_PRINTF_HIDE ( stderr );
	CONSOLE_change_color ( col );
}

void CONSOLE_wprintf_gpu_error ( eGPU_error_level err_level , const wchar_t *fmt , ... ) {
	unsigned short col = CONSOLE_get_current_color ( );
	CONSOLE_change_color ( CONSOLE_color_from_gpu_error_level ( err_level ) );
	CONSOLE_WPRINTF_HIDE ( stderr );
	CONSOLE_change_color ( col );
}
