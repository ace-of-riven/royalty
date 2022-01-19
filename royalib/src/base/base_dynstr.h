#pragma once

#include <stdarg.h>

// dynamic c string implementation

typedef struct DynStr DynStr;

DynStr *BASE_dynstr_new ( void ) ;

void BASE_dynstr_append ( DynStr *__restrict ds , const char *cstr ) ;
void BASE_dynstr_nappend ( DynStr *__restrict ds , const char *cstr , int len ) ;

void BASE_dynstr_appendf ( DynStr *__restrict ds , const char *__restrict format , ... );
void BASE_dynstr_vappendf ( DynStr *__restrict ds , const char *__restrict format , va_list args );

int BASE_dynstr_get_len ( const DynStr *ds );
char *BASE_dynstr_get_cstring ( const DynStr *ds );
void BASE_dynstr_get_cstring_ex ( const DynStr *__restrict ds , char *__restrict rets );

void BASE_dynstr_clear ( DynStr *ds );
void BASE_dynstr_free ( DynStr *ds );
