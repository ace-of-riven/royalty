#include "../base_hash.h"

#define DNA_HASH_BASE64				881
#define DNA_HASH_BASE32				465
#define DNA_HASH_BASE16				277
#define DNA_HASH_BASE8				67

unsigned long long DNA_hash_buffer64 ( const void *buffer , unsigned long long length ) {
	unsigned long long answer = 0 ;
	for ( unsigned long long idx = 0; idx < length; idx++ )
		answer = answer * DNA_HASH_BASE64 + ( ( const char * ) buffer ) [ idx ] ;
	return answer ;
}

unsigned int DNA_hash_buffer32 ( const void *buffer , unsigned long long length ) {
	unsigned int answer = 0;
	for ( unsigned long long idx = 0; idx < length; idx++ )
		answer = answer * DNA_HASH_BASE32 + ( ( const char * ) buffer ) [ idx ];
	return answer;
}

unsigned short DNA_hash_buffer16 ( const void *buffer , unsigned long long length ) {
	unsigned short answer = 0;
	for ( unsigned long long idx = 0; idx < length; idx++ )
		answer = answer * DNA_HASH_BASE16 + ( ( const char * ) buffer ) [ idx ];
	return answer;
}

unsigned char DNA_hash_buffer8 ( const void *buffer , unsigned long long length ) {
	unsigned char answer = 0;
	for ( unsigned long long idx = 0; idx < length; idx++ )
		answer = answer * DNA_HASH_BASE8 + ( ( const char * ) buffer ) [ idx ];
	return answer;
}

std::string DNA_string_to_key8_advanced ( const std::string &user_key , unsigned long long base ) {
	unsigned int hash = base ;
	for ( unsigned long long i = 0; i < user_key.length ( ); i++ ) {
		hash = hash * base + user_key [ i ] ;
	}
	char c_result [ 12 ];
	sprintf_s ( c_result , 12 , "%08llx" , hash );
	return c_result;
}
std::string DNA_string_to_key16_advanced ( const std::string &user_key , unsigned long long base ) {
	unsigned long long hash = base;
	for ( unsigned long long i = 0; i < user_key.length ( ); i++ ) {
		hash = hash * base + user_key [ i ];
	}
	char c_result [ 24 ];
	sprintf_s ( c_result , 24 , "%016llx" , hash );
	return c_result;
}


std::string DNA_string_to_key8 ( const std::string &user_key ) {
	return DNA_string_to_key8_advanced ( user_key , 347 ) ;
}

std::string DNA_string_to_key16 ( const std::string &user_key ) {
	return DNA_string_to_key8_advanced ( user_key , 257 ) +
		DNA_string_to_key8_advanced ( user_key , 347 ) ;
}

std::string DNA_string_to_key24 ( const std::string &user_key ) {
	return DNA_string_to_key8_advanced ( user_key , 347 ) +
		DNA_string_to_key8_advanced ( user_key , 241 ) +
		DNA_string_to_key8_advanced ( user_key , 149 );
}

std::string DNA_string_to_key32 ( const std::string &user_key ) {
	return DNA_string_to_key16_advanced ( user_key , 347 ) +
		DNA_string_to_key16_advanced ( user_key , 907 ) ;
}
