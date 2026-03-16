rfbBool rfbFilenameTranslate2UNIX ( rfbClientPtr cl , char * path , char * unixPath , size_t unixPathMaxLen ) {
 int x ;
 char * home = NULL ;
 FILEXFER_ALLOWED_OR_CLOSE_AND_RETURN ( "" , cl , FALSE ) ;
 if ( strlen ( path ) >= unixPathMaxLen ) return FALSE ;
 if ( path [ 0 ] == 'C' && path [ 1 ] == ':' ) strcpy ( unixPath , & path [ 2 ] ) ;
 else {
 home = getenv ( "HOME" ) ;
 if ( home != NULL ) {
 if ( ( strlen ( path ) + strlen ( home ) + 1 ) >= unixPathMaxLen ) return FALSE ;
 strcpy ( unixPath , home ) ;
 strcat ( unixPath , "/" ) ;
 strcat ( unixPath , path ) ;
 }
 else strcpy ( unixPath , path ) ;
 }
 for ( x = 0 ;
 x < strlen ( unixPath ) ;
 x ++ ) if ( unixPath [ x ] == '\\' ) unixPath [ x ] = '/' ;
 return TRUE ;
 }