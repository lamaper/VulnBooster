gpg_error_t keydb_search_next ( KEYDB_HANDLE hd ) {
 gpg_error_t err ;
 KEYDB_SEARCH_DESC desc ;
 do {
 memset ( & desc , 0 , sizeof desc ) ;
 desc . mode = KEYDB_SEARCH_MODE_NEXT ;
 err = keydb_search ( hd , & desc , 1 , NULL ) ;
 }
 while ( gpg_err_code ( err ) == GPG_ERR_LEGACY_KEY ) ;
 return err ;
 }