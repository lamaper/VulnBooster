static int prefix_array ( const char * dirname , char * * array , size_t n ) {
 register size_t i ;
 size_t dirlen = strlen ( dirname ) ;



 if ( dirname [ dirlen - 1 ] == '/' && dirname [ dirlen - 2 ] == ':' ) -- dirlen ;
 else if ( dirname [ dirlen - 1 ] == ':' ) {
 -- dirlen ;
 sep_char = ':' ;
 }
 }

 i < n ;
 ++ i ) {
 size_t eltlen = strlen ( array [ i ] ) + 1 ;
 char * new = ( char * ) malloc ( dirlen + 1 + eltlen ) ;
 if ( new == NULL ) {
 while ( i > 0 ) free ( array [ -- i ] ) ;
 return 1 ;
 }
 {
 char * endp = mempcpy ( new , dirname , dirlen ) ;
 * endp ++ = DIRSEP_CHAR ;
 mempcpy ( endp , array [ i ] , eltlen ) ;
 }
 free ( array [ i ] ) ;
 array [ i ] = new ;
 }
 return 0 ;
 }