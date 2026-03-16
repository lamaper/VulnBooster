static void fixDirToTreePath ( char * s ) {
 ( void ) s ;


 t = uprv_strchr ( t , U_FILE_SEP_CHAR ) ;
 ) {
 * t = U_TREE_ENTRY_SEP_CHAR ;
 }

 t = uprv_strchr ( t , U_FILE_ALT_SEP_CHAR ) ;
 ) {
 * t = U_TREE_ENTRY_SEP_CHAR ;
 }
