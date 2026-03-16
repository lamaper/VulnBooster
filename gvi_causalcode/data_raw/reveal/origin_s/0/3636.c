void get_dirname ( char * dirname , const char * filename ) {
 const char * lastSlash = uprv_strrchr ( filename , U_FILE_SEP_CHAR ) + 1 ;
 if ( lastSlash > filename ) {
 uprv_strncpy ( dirname , filename , ( lastSlash - filename ) ) ;
 * ( dirname + ( lastSlash - filename ) ) = '\0' ;
 }
 else {
 * dirname = '\0' ;
 }
 }