gpg_error_t keydb_search_first ( KEYDB_HANDLE hd ) {
 gpg_error_t err ;
 KEYDB_SEARCH_DESC desc ;
 memset ( & desc , 0 , sizeof desc ) ;
 desc . mode = KEYDB_SEARCH_MODE_FIRST ;
 err = keydb_search ( hd , & desc , 1 , NULL ) ;
 if ( gpg_err_code ( err ) == GPG_ERR_LEGACY_KEY ) err = keydb_search_next ( hd ) ;
 return err ;
 }