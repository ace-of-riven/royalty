#define _CRT_SECURE_NO_WARNINGS

#include "../base_file.h"

#include <fstream>
#include <streambuf>

void *DNA_file_to_str ( FILE *in , unsigned long long *size ) {
	_fseeki64 ( in , 0 , SEEK_END );
	unsigned long long sz = _ftelli64 ( in );
	if ( size )
		*size = sz;
	char *pb = new char [ sz + 1 ];
	memset ( pb , 0 , sz + 1 );
	fseek ( in , 0 , SEEK_SET );
	fread ( pb , 1 , sz , in );
	fclose ( in );
	return pb;
}

void *DNA_file_to_byes ( FILE *in , unsigned long long *size ) {
	_fseeki64 ( in , 0 , SEEK_END );
	unsigned long long sz = _ftelli64 ( in );
	if ( size )
		*size = sz;
	char *pb = new char [ sz ];
	fseek ( in , 0 , SEEK_SET );
	fread ( pb , 1 , sz , in );
	fclose ( in );
	return pb;
}

void *DNA_file_read ( const wchar_t *filename , unsigned long long *size ) {
	FILE *in = _wfopen ( filename , L"rb" );
	return DNA_file_to_str ( in , size );
}

void *DNA_file_read ( const char *filename , unsigned long long *size ) {
	FILE *in = fopen ( filename , "rb" );
	if ( in )
		return DNA_file_to_str ( in , size );
	if ( size )
		*size = 0;
	return NULL;
}

void *DNA_file_read_binary ( const char *filename , unsigned long long *size ) {
	FILE *in = fopen ( filename , "rb" );
	if ( in )
		return DNA_file_to_byes ( in , size );
	if ( size )
		*size = 0;
	return NULL;
}
void *DNA_file_read_binary ( const wchar_t *filename , unsigned long long *size ) {
	FILE *in = _wfopen ( filename , L"rb" );
	if ( in )
		return DNA_file_to_byes ( in , size );
	if ( size )
		*size = 0;
	return NULL;
}
