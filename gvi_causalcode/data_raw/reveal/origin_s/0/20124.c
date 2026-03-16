gpg_error_t keydb_delete_keyblock ( KEYDB_HANDLE hd ) {
 gpg_error_t rc ;
 if ( ! hd ) return gpg_error ( GPG_ERR_INV_ARG ) ;
 keyblock_cache_clear ( ) ;
 if ( hd -> found < 0 || hd -> found >= hd -> used ) return gpg_error ( GPG_ERR_VALUE_NOT_FOUND ) ;
 if ( opt . dry_run ) return 0 ;
 rc = lock_all ( hd ) ;
 if ( rc ) return rc ;
 switch ( hd -> active [ hd -> found ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : rc = gpg_error ( GPG_ERR_GENERAL ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : rc = keyring_delete_keyblock ( hd -> active [ hd -> found ] . u . kr ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : rc = keybox_delete ( hd -> active [ hd -> found ] . u . kb ) ;
 break ;
 }
 unlock_all ( hd ) ;
 return rc ;
 }