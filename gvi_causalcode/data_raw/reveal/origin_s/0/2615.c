gpg_error_t keydb_insert_keyblock ( KEYDB_HANDLE hd , kbnode_t kb ) {
 gpg_error_t err ;
 int idx ;
 if ( ! hd ) return gpg_error ( GPG_ERR_INV_ARG ) ;
 keyblock_cache_clear ( ) ;
 if ( opt . dry_run ) return 0 ;
 if ( hd -> found >= 0 && hd -> found < hd -> used ) idx = hd -> found ;
 else if ( hd -> current >= 0 && hd -> current < hd -> used ) idx = hd -> current ;
 else return gpg_error ( GPG_ERR_GENERAL ) ;
 err = lock_all ( hd ) ;
 if ( err ) return err ;
 switch ( hd -> active [ idx ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : err = gpg_error ( GPG_ERR_GENERAL ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : err = keyring_insert_keyblock ( hd -> active [ idx ] . u . kr , kb ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : {
 iobuf_t iobuf ;
 u32 * sigstatus ;
 err = build_keyblock_image ( kb , & iobuf , & sigstatus ) ;
 if ( ! err ) {
 err = keybox_insert_keyblock ( hd -> active [ idx ] . u . kb , iobuf_get_temp_buffer ( iobuf ) , iobuf_get_temp_length ( iobuf ) , sigstatus ) ;
 xfree ( sigstatus ) ;
 iobuf_close ( iobuf ) ;
 }
 }
 break ;
 }
 unlock_all ( hd ) ;
 return err ;
 }