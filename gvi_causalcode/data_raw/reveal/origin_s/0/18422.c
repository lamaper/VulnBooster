static char * safeGetICUDataDirectory ( ) {
 const char * dataDir = u_getDataDirectory ( ) ;
 char * retStr = NULL ;
 if ( dataDir != NULL ) {
 retStr = ( char * ) malloc ( strlen ( dataDir ) + 1 ) ;
 strcpy ( retStr , dataDir ) ;
 }
 return retStr ;
 }