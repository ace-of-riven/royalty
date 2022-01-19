#pragma once

#include <string>

unsigned long long DNA_hash_buffer64 ( const void *buffer , unsigned long long length ) ;
unsigned int DNA_hash_buffer32 ( const void *buffer , unsigned long long length ) ;
unsigned short DNA_hash_buffer16 ( const void *buffer , unsigned long long length ) ;
unsigned char DNA_hash_buffer8 ( const void *buffer , unsigned long long length ) ;

std::string DNA_string_to_key8 ( const std::string &user_key );
std::string DNA_string_to_key16 ( const std::string &user_key );
std::string DNA_string_to_key24 ( const std::string &user_key );
std::string DNA_string_to_key32 ( const std::string &user_key );
