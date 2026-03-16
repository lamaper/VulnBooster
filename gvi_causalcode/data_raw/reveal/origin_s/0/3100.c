gpg_error_t keydb_search_fpr ( KEYDB_HANDLE hd , const byte * fpr ) {
 KEYDB_SEARCH_DESC desc ;
 memset ( & desc , 0 , sizeof desc ) ;
 desc . mode = KEYDB_SEARCH_MODE_FPR ;
 memcpy ( desc . u . fpr , fpr , MAX_FINGERPRINT_LEN ) ;
 return keydb_search ( hd , & desc , 1 , NULL ) ;
 }