static cmsBool isabsolutepath ( const char * path ) {
 char ThreeChars [ 4 ] ;
 if ( path == NULL ) return FALSE ;
 if ( path [ 0 ] == 0 ) return FALSE ;
 strncpy ( ThreeChars , path , 3 ) ;
 ThreeChars [ 3 ] = 0 ;
 if ( ThreeChars [ 0 ] == DIR_CHAR ) return TRUE ;


 }