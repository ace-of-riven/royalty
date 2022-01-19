#include <malloc.h>
#include <string.h>

#include "../base_string.h"

/**
 * Duplicates the first \a len bytes of cstring \a str
 * into a newly malloc'd string and returns it. \a str
 * is assumed to be at least len bytes long.
 *
 * \param str: The string to be duplicated
 * \param len: The number of bytes to duplicate
 * \retval Returns the duplicated string
 */
char *BLI_strdupn ( const char *str , const size_t len )
{
	char *n = ( char * ) malloc ( len + 1 );
	memcpy ( n , str , len );
	n [ len ] = '\0';

	return n;
}

/**
 * Duplicates the cstring \a str into a newly mallocN'd
 * string and returns it.
 *
 * \param str: The string to be duplicated
 * \retval Returns the duplicated string
 */
char *BASE_strdup ( const char *str ) {
	return BLI_strdupn ( str , strlen ( str ) );
}
