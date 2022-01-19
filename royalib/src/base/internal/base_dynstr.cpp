#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <stdarg.h>
#include <assert.h>

#include "../base_dynstr.h"

#ifdef _WIN32
#  ifndef vsnprintf
#    define vsnprintf _vsnprintf
#  endif
#endif

#ifndef va_copy
#  ifdef __va_copy
#    define va_copy(a, b) __va_copy(a, b)
#  else /* !__va_copy */
#    define va_copy(a, b) ((a) = (b))
#  endif /* __va_copy */
#endif   /* va_copy */

typedef struct DynStrElem DynStrElem;

struct DynStrElem {
	DynStrElem *next;

	char *str;
};

struct DynStr {
	DynStrElem *elems , *last;
	int curlen;
};

DynStr *BASE_dynstr_new ( void ) {
	DynStr *ds = ( DynStr * ) malloc ( sizeof ( *ds ) );
	ds->elems = ds->last = NULL;
	ds->curlen = 0;
	return ds;
}

/* determine the length of a fixed-size string */
static size_t _strnlen ( const char *str , size_t maxlen ) {
	const char *end = ( const char * ) memchr ( str , '\0' , maxlen );
	return end ? ( size_t ) ( end - str ) : maxlen;
}

static void *_dynstr_alloc ( DynStr *__restrict ds , size_t size ) {
	return malloc ( size );
}

/**
 * Append a c-string to a DynStr.
 *
 * \param ds: The DynStr to append to.
 * \param cstr: The c-string to append.
 */
void BASE_dynstr_append ( DynStr *__restrict ds , const char *cstr ) {
	DynStrElem *dse = ( DynStrElem * ) _dynstr_alloc ( ds , sizeof ( *dse ) );
	int cstrlen = strlen ( cstr );

	dse->str = ( char * ) _dynstr_alloc ( ds , cstrlen + 1 );
	memcpy ( dse->str , cstr , cstrlen + 1 );
	dse->next = NULL;

	if ( !ds->last ) {
		ds->last = ds->elems = dse;
	}
	else {
		ds->last = ds->last->next = dse;
	}

	ds->curlen += cstrlen;
}

/**
 * Append a length clamped c-string to a DynStr.
 *
 * \param ds: The DynStr to append to.
 * \param cstr: The c-string to append.
 * \param len: The maximum length of the c-string to copy.
 */
void BASE_dynstr_nappend ( DynStr *__restrict ds , const char *cstr , int len ) {
	DynStrElem *dse = ( DynStrElem * ) _dynstr_alloc ( ds , sizeof ( *dse ) );
	int cstrlen = _strnlen ( cstr , len );

	dse->str = ( char * ) _dynstr_alloc ( ds , cstrlen + 1 );
	memcpy ( dse->str , cstr , cstrlen );
	dse->str [ cstrlen ] = '\0';
	dse->next = NULL;

	if ( !ds->last ) {
		ds->last = ds->elems = dse;
	}
	else {
		ds->last = ds->last->next = dse;
	}

	ds->curlen += cstrlen;
}

/**
 * Append a c-string to a DynStr, but with formatting like printf.
 *
 * \param ds: The DynStr to append to.
 * \param format: The printf format string to use.
 */
void BASE_dynstr_appendf ( DynStr *__restrict ds , const char *__restrict format , ... ) {
	va_list args;
	char *message , fixedmessage [ 256 ];
	int len = sizeof ( fixedmessage );
	const int maxlen = 65536;
	int retval;

	/* note that it's tempting to just call BLI_dynstr_vappendf here
	 * and avoid code duplication, that crashes on some system because
	 * va_start/va_end have to be called for each vsnprintf call */

	while ( 1 ) {
		if ( len == sizeof ( fixedmessage ) ) {
			message = fixedmessage;
		}
		else {
			message = ( char * ) malloc ( sizeof ( char ) * ( len ) );
		}

		va_start ( args , format );
		retval = vsnprintf ( message , len , format , args );
		va_end ( args );

		if ( retval == -1 ) {
			/* -1 means not enough space, but on windows it may also mean
			 * there is a formatting error, so we impose a maximum length */
			if ( message != fixedmessage ) {
				free ( message );
			}
			message = NULL;

			len *= 2;
			if ( len > maxlen ) {
				fprintf ( stderr , "BLI_dynstr_append text too long or format error.\n" );
				break;
			}
		}
		else if ( retval >= len ) {
			/* in C99 the actual length required is returned */
			if ( message != fixedmessage ) {
				free ( message );
			}
			message = NULL;

			/* retval doesn't include \0 terminator */
			len = retval + 1;
		}
		else {
			break;
		}
	}

	if ( message ) {
		BASE_dynstr_append ( ds , message );

		if ( message != fixedmessage ) {
			free ( message );
		}
	}
}

void BASE_dynstr_vappendf ( DynStr *__restrict ds , const char *__restrict format , va_list args ) {
	char *message , fixedmessage [ 256 ];
	int len = sizeof ( fixedmessage );
	const int maxlen = 65536;
	int retval;

	while ( 1 ) {
		va_list args_cpy;
		if ( len == sizeof ( fixedmessage ) ) {
			message = fixedmessage;
		}
		else {
			message = ( char * ) malloc ( sizeof ( char ) * len );
		}

		/* can't reuse the same args, so work on a copy */
		va_copy ( args_cpy , args );
		retval = vsnprintf ( message , len , format , args_cpy );
		va_end ( args_cpy );

		if ( retval == -1 ) {
			/* -1 means not enough space, but on windows it may also mean
			 * there is a formatting error, so we impose a maximum length */
			if ( message != fixedmessage ) {
				free ( message );
			}
			message = NULL;

			len *= 2;
			if ( len > maxlen ) {
				fprintf ( stderr , "BASE_dynstr_append text too long or format error.\n" );
				break;
			}
		}
		else if ( retval >= len ) {
			/* in C99 the actual length required is returned */
			if ( message != fixedmessage ) {
				free ( message );
			}
			message = NULL;

			/* retval doesn't include \0 terminator */
			len = retval + 1;
		}
		else {
			break;
		}
	}

	if ( message ) {
		BASE_dynstr_append ( ds , message );

		if ( message != fixedmessage ) {
			free ( message );
		}
	}
}

int BASE_dynstr_get_len ( const DynStr *ds ) {
	return ds->curlen;
}

/**
 * Get a DynStr's contents as a c-string.
 * <i> The returned c-string should be freed
 * using free. </i>
 *
 * \param ds: The DynStr of interest.
 * \return The contents of \a ds as a c-string.
 */
char *BASE_dynstr_get_cstring ( const DynStr *ds ) {
	char *rets = ( char * ) malloc ( ds->curlen + 1 );
	BASE_dynstr_get_cstring_ex ( ds , rets );
	return rets;
}

/**
 * Get a DynStr's contents as a c-string.
 * The \a rets argument must be allocated to be at
 * least the size of `BASE_dynstr_get_len(ds) + 1`.
 *
 * \param ds: The DynStr of interest.
 * \param rets: The string to fill.
 */
void BASE_dynstr_get_cstring_ex ( const DynStr *__restrict ds , char *__restrict rets ) {
	char *s;
	const DynStrElem *dse;

	for ( s = rets , dse = ds->elems; dse; dse = dse->next ) {
		int slen = strlen ( dse->str );

		memcpy ( s , dse->str , slen );

		s += slen;
	}
	assert ( ( s - rets ) == ds->curlen );
	rets [ ds->curlen ] = '\0';
}

/**
 * Clear the DynStr
 *
 * \param ds: The DynStr to clear.
 */
void BASE_dynstr_clear ( DynStr *ds ) {
	for ( DynStrElem *dse_next , *dse = ds->elems; dse; dse = dse_next ) {
		dse_next = dse->next;

		free ( dse->str );
		free ( dse );
	}

	ds->elems = ds->last = NULL;
	ds->curlen = 0;
}

/**
 * Free the DynStr
 *
 * \param ds: The DynStr to free.
 */
void BASE_dynstr_free ( DynStr *ds ) {
	BASE_dynstr_clear ( ds );
	free ( ds ) ;
}