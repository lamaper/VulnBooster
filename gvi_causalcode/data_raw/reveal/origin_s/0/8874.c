void get_basename ( char * basename , const char * filename ) {
 const char * lastSlash = uprv_strrchr ( filename , U_FILE_SEP_CHAR ) + 1 ;
 char * lastDot ;
 if ( lastSlash > filename ) {
 uprv_strcpy ( basename , lastSlash ) ;
 }
 else {
 uprv_strcpy ( basename , filename ) ;
 }
 lastDot = uprv_strrchr ( basename , '.' ) ;
 if ( lastDot != NULL ) {
 * lastDot = '\0' ;
 }
 }