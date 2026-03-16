const char * pkg_writeCharListWrap ( FileStream * s , CharList * l , const char * delim , const char * brk , int32_t quote ) {
 int32_t ln = 0 ;
 char buffer [ 1024 ] ;
 while ( l != NULL ) {
 if ( l -> str ) {
 uprv_strncpy ( buffer , l -> str , 1020 ) ;
 buffer [ 1019 ] = 0 ;
 if ( quote < 0 ) {
 if ( buffer [ uprv_strlen ( buffer ) - 1 ] == '"' ) {
 buffer [ uprv_strlen ( buffer ) - 1 ] = '\0' ;
 }
 if ( buffer [ 0 ] == '"' ) {
 uprv_strcpy ( buffer , buffer + 1 ) ;
 }
 }
 else if ( quote > 0 ) {
 if ( l -> str [ 0 ] != '"' ) {
 uprv_strcpy ( buffer , "\"" ) ;
 uprv_strncat ( buffer , l -> str , 1020 ) ;
 }
 if ( l -> str [ uprv_strlen ( l -> str ) - 1 ] != '"' ) {
 uprv_strcat ( buffer , "\"" ) ;
 }
 }
 T_FileStream_write ( s , buffer , ( int32_t ) uprv_strlen ( buffer ) ) ;
 ln += ( int32_t ) uprv_strlen ( l -> str ) ;
 }
 if ( l -> next && delim ) {
 if ( ln > 60 && brk ) {
 ln = 0 ;
 T_FileStream_write ( s , brk , ( int32_t ) uprv_strlen ( brk ) ) ;
 }
 T_FileStream_write ( s , delim , ( int32_t ) uprv_strlen ( delim ) ) ;
 }
 l = l -> next ;
 }
 return NULL ;
 }