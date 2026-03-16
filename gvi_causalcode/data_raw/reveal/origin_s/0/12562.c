char * convertToNativePathSeparators ( char * path ) {

 while ( ( itr = uprv_strchr ( path , U_FILE_ALT_SEP_CHAR ) ) ) {
 * itr = U_FILE_SEP_CHAR ;
 }

 }