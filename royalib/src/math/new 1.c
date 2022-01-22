#include <stdio.h>

struct STRUCT_NAME1 {
	char *NAME;
	int ID;
}

struct STRUCT_NAME {
	int DATA0 ;
	int DATA1 ;
	float DATA2; // f <float>
	double DATA3; // lf <long float>
	
	STRUCT_NAME1 CUSTOMER0;
	STRUCT_NAME1 CUSTOMER1;
	STRUCT_NAME1 CUSTOMER2;
};

void f ( const STRUCT_NAME *a , const STRUCT_NAME1 *b ) {
	
}

void f ( STRUCT_NAME a , STRUCT_NAME v , STRUCT_NAME1 b , ... ) {
	a.DATA0 = 1 ;
	a.DATA1 = 1 ;
	a.DATA2 = 1 ;
	a.DATA3 = 1 ;
	a.DATA4.ID = b.ID ;
}

int main ( ) {
	STRUCT_NAME VAR ;
	VAR.DATA0 = 0 ;
	VAR.DATA1 = 0 ;
	VAR.DATA2 = 0 ;
	VAR.DATA3 = 0 ;
	VAR.DATA4.ID = 0 ;
	VAR.DATA5.ID = 0 ;
	VAR.DATA6.ID = 0 ;
	
	STRUCT_NAME1 VAR1;
	VAR1.ID = 5;
	
	f ( &VAR , &VAR1 ) ;
	f ( VAR , VAR1 ) ;
	return 0;
}