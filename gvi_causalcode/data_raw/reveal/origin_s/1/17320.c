static int xsltCheckFilename ( const char * path ) {


 dwAttrs = GetFileAttributesA ( path ) ;
 if ( dwAttrs != INVALID_FILE_ATTRIBUTES ) {
 if ( dwAttrs & FILE_ATTRIBUTE_DIRECTORY ) {
 return 2 ;
 }
 }


 return 2 ;
 }

 }