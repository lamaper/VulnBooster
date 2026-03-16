void keydb_rebuild_caches ( int noisy ) {
 int i , rc ;
 keyblock_cache_clear ( ) ;
 for ( i = 0 ;
 i < used_resources ;
 i ++ ) {
 if ( ! keyring_is_writable ( all_resources [ i ] . token ) ) continue ;
 switch ( all_resources [ i ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : rc = keyring_rebuild_cache ( all_resources [ i ] . token , noisy ) ;
 if ( rc ) log_error ( _ ( "failed to rebuild keyring cache: %s\n" ) , gpg_strerror ( rc ) ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : break ;
 }
 }
 }