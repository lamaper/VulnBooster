CharList * pkg_appendUniqueDirToList ( CharList * l , CharList * * end , const char * strAlias ) {
 char aBuf [ 1024 ] ;
 char * rPtr ;
 rPtr = uprv_strrchr ( strAlias , U_FILE_SEP_CHAR ) ;

 char * aPtr = uprv_strrchr ( strAlias , U_FILE_ALT_SEP_CHAR ) ;
 if ( ! rPtr || ( aPtr && ( aPtr > rPtr ) ) ) {
 rPtr = aPtr ;
 }
 }

 return l ;
 }
 if ( ( rPtr - strAlias ) >= UPRV_LENGTHOF ( aBuf ) ) {
 fprintf ( stderr , "## ERR: Path too long [%d chars]: %s\n" , ( int ) sizeof ( aBuf ) , strAlias ) ;
 return l ;
 }
 strncpy ( aBuf , strAlias , ( rPtr - strAlias ) ) ;
 aBuf [ rPtr - strAlias ] = 0 ;
 convertToNativePathSeparators ( aBuf ) ;
 if ( ! pkg_listContains ( l , aBuf ) ) {
 return pkg_appendToList ( l , end , uprv_strdup ( aBuf ) ) ;
 }
 else {
 return l ;
 }
 }