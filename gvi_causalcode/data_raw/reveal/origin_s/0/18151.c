void DerFree ( Asn1Generic * a ) {
 Asn1Generic * it , * n ;
 if ( a == NULL ) return ;
 it = a ;
 while ( it ) {
 n = it -> next ;
 if ( it -> data ) {
 DerFree ( it -> data ) ;
 }
 if ( it -> str ) SCFree ( it -> str ) ;
 memset ( it , 0xff , sizeof ( Asn1Generic ) ) ;
 SCFree ( it ) ;
 it = n ;
 }
 }