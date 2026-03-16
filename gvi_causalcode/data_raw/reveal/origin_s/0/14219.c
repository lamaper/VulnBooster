gpg_error_t keydb_update_keyblock ( KEYDB_HANDLE hd , kbnode_t kb ) {
 gpg_error_t err ;
 if ( ! hd ) return gpg_error ( GPG_ERR_INV_ARG ) ;
 keyblock_cache_clear ( ) ;
 if ( hd -> found < 0 || hd -> found >= hd -> used ) return gpg_error ( GPG_ERR_VALUE_NOT_FOUND ) ;
 if ( opt . dry_run ) return 0 ;
 err = lock_all ( hd ) ;
 if ( err ) return err ;
 switch ( hd -> active [ hd -> found ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : err = gpg_error ( GPG_ERR_GENERAL ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : err = keyring_update_keyblock ( hd -> active [ hd -> found ] . u . kr , kb ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : {
 iobuf_t iobuf ;
 err = build_keyblock_image ( kb , & iobuf , NULL ) ;
 if ( ! err ) {
 err = keybox_update_keyblock ( hd -> active [ hd -> found ] . u . kb , iobuf_get_temp_buffer ( iobuf ) , iobuf_get_temp_length ( iobuf ) ) ;
 iobuf_close ( iobuf ) ;
 }
 }
 break ;
 }
 unlock_all ( hd ) ;
 return err ;
 }