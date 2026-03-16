gpg_error_t keydb_search_kid ( KEYDB_HANDLE hd , u32 * kid ) {
 KEYDB_SEARCH_DESC desc ;
 memset ( & desc , 0 , sizeof desc ) ;
 desc . mode = KEYDB_SEARCH_MODE_LONG_KID ;
 desc . u . kid [ 0 ] = kid [ 0 ] ;
 desc . u . kid [ 1 ] = kid [ 1 ] ;
 return keydb_search ( hd , & desc , 1 , NULL ) ;
 }