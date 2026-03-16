gpg_error_t keydb_search ( KEYDB_HANDLE hd , KEYDB_SEARCH_DESC * desc , size_t ndesc , size_t * descindex ) {
 gpg_error_t rc ;
 if ( descindex ) * descindex = 0 ;
 if ( ! hd ) return gpg_error ( GPG_ERR_INV_ARG ) ;
 if ( DBG_CLOCK ) log_clock ( "keydb_search enter" ) ;
 if ( DBG_CACHE ) dump_search_desc ( hd , "keydb_search" , desc , ndesc ) ;
 if ( ! hd -> no_caching && ndesc == 1 && ( desc [ 0 ] . mode == KEYDB_SEARCH_MODE_FPR20 || desc [ 0 ] . mode == KEYDB_SEARCH_MODE_FPR ) && keyblock_cache . state == KEYBLOCK_CACHE_FILLED && ! memcmp ( keyblock_cache . fpr , desc [ 0 ] . u . fpr , 20 ) ) {
 if ( DBG_CLOCK ) log_clock ( "keydb_search leave (cached)" ) ;
 return 0 ;
 }
 rc = - 1 ;
 while ( ( rc == - 1 || gpg_err_code ( rc ) == GPG_ERR_EOF ) && hd -> current >= 0 && hd -> current < hd -> used ) {
 switch ( hd -> active [ hd -> current ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : BUG ( ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : rc = keyring_search ( hd -> active [ hd -> current ] . u . kr , desc , ndesc , descindex ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : rc = keybox_search ( hd -> active [ hd -> current ] . u . kb , desc , ndesc , KEYBOX_BLOBTYPE_PGP , descindex , & hd -> skipped_long_blobs ) ;
 break ;
 }
 if ( rc == - 1 || gpg_err_code ( rc ) == GPG_ERR_EOF ) {
 hd -> current ++ ;
 }
 else if ( ! rc ) hd -> found = hd -> current ;
 }
 rc = ( ( rc == - 1 || gpg_err_code ( rc ) == GPG_ERR_EOF ) ? gpg_error ( GPG_ERR_NOT_FOUND ) : rc ) ;
 keyblock_cache_clear ( ) ;
 if ( ! hd -> no_caching && ! rc && ndesc == 1 && ( desc [ 0 ] . mode == KEYDB_SEARCH_MODE_FPR20 || desc [ 0 ] . mode == KEYDB_SEARCH_MODE_FPR ) ) {
 keyblock_cache . state = KEYBLOCK_CACHE_PREPARED ;
 memcpy ( keyblock_cache . fpr , desc [ 0 ] . u . fpr , 20 ) ;
 }
 if ( DBG_CLOCK ) log_clock ( rc ? "keydb_search leave (not found)" : "keydb_search leave (found)" ) ;
 return rc ;
 }