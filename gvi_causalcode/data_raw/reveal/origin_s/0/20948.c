gpg_error_t keydb_search_reset ( KEYDB_HANDLE hd ) {
 gpg_error_t rc = 0 ;
 int i ;
 if ( ! hd ) return gpg_error ( GPG_ERR_INV_ARG ) ;
 keyblock_cache_clear ( ) ;
 if ( DBG_CLOCK ) log_clock ( "keydb_search_reset" ) ;
 if ( DBG_CACHE ) log_debug ( "keydb_search: reset (hd=%p)" , hd ) ;
 hd -> skipped_long_blobs = 0 ;
 hd -> current = 0 ;
 hd -> found = - 1 ;
 for ( i = 0 ;
 ! rc && i < hd -> used ;
 i ++ ) {
 switch ( hd -> active [ i ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : rc = keyring_search_reset ( hd -> active [ i ] . u . kr ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : rc = keybox_search_reset ( hd -> active [ i ] . u . kb ) ;
 break ;
 }
 }
 return rc ;
 }