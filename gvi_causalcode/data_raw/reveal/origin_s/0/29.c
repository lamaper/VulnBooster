void addToHeaderList ( const char * strings [ ] , HttpHeaderList & headers ) {
 for ( int i = 0 ;
 strings [ i ] ;
 i += 2 ) {
 if ( i % 4 == 0 ) {
 headers . push_back ( HttpHeader ( strings [ i ] , - 1 , strings [ i + 1 ] , - 1 ) ) ;
 headers . push_back ( HttpHeader ( ) ) ;
 }
 else {
 headers . push_back ( HttpHeader ( strings [ i ] , strlen ( strings [ i ] ) , strings [ i + 1 ] , strlen ( strings [ i + 1 ] ) ) ) ;
 }
 }
 }