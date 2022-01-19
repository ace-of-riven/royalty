#pragma once

void *DNA_file_read ( const char *filename , unsigned long long *size );
void *DNA_file_read ( const wchar_t *filename , unsigned long long *size );

void *DNA_file_read_binary ( const char *filename , unsigned long long *size );
void *DNA_file_read_binary ( const wchar_t *filename , unsigned long long *size );
