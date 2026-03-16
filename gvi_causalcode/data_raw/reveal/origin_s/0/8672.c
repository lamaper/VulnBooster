const char * pkg_writeCharList ( FileStream * s , CharList * l , const char * delim , int32_t quote ) {
 char buffer [ 1024 ] ;
 while ( l != NULL ) {
 if ( l -> str ) {
 uprv_strncpy ( buffer , l -> str , 1023 ) ;
 buffer [ 1023 ] = 0 ;
 if ( uprv_strlen ( l -> str ) >= 1023 ) {
 fprintf ( stderr , "%s:%d: Internal error, line too long (greater than 1023 chars)\n" , __FILE__ , __LINE__ ) ;
 exit ( 0 ) ;
 }
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
 uprv_strcat ( buffer , l -> str ) ;
 }
 if ( l -> str [ uprv_strlen ( l -> str ) - 1 ] != '"' ) {
 uprv_strcat ( buffer , "\"" ) ;
 }
 }
 T_FileStream_write ( s , buffer , ( int32_t ) uprv_strlen ( buffer ) ) ;
 }
 if ( l -> next && delim ) {
 T_FileStream_write ( s , delim , ( int32_t ) uprv_strlen ( delim ) ) ;
 }
 l = l -> next ;
 }
 return NULL ;
 }