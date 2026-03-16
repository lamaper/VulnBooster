gpg_error_t keydb_get_keyblock ( KEYDB_HANDLE hd , KBNODE * ret_kb ) {
 gpg_error_t err = 0 ;
 * ret_kb = NULL ;
 if ( ! hd ) return gpg_error ( GPG_ERR_INV_ARG ) ;
 if ( keyblock_cache . state == KEYBLOCK_CACHE_FILLED ) {
 iobuf_seek ( keyblock_cache . iobuf , 0 ) ;
 err = parse_keyblock_image ( keyblock_cache . iobuf , keyblock_cache . pk_no , keyblock_cache . uid_no , keyblock_cache . sigstatus , ret_kb ) ;
 if ( err ) keyblock_cache_clear ( ) ;
 return err ;
 }
 if ( hd -> found < 0 || hd -> found >= hd -> used ) return gpg_error ( GPG_ERR_VALUE_NOT_FOUND ) ;
 switch ( hd -> active [ hd -> found ] . type ) {
 case KEYDB_RESOURCE_TYPE_NONE : err = gpg_error ( GPG_ERR_GENERAL ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYRING : err = keyring_get_keyblock ( hd -> active [ hd -> found ] . u . kr , ret_kb ) ;
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : {
 iobuf_t iobuf ;
 u32 * sigstatus ;
 int pk_no , uid_no ;
 err = keybox_get_keyblock ( hd -> active [ hd -> found ] . u . kb , & iobuf , & pk_no , & uid_no , & sigstatus ) ;
 if ( ! err ) {
 err = parse_keyblock_image ( iobuf , pk_no , uid_no , sigstatus , ret_kb ) ;
 if ( ! err && keyblock_cache . state == KEYBLOCK_CACHE_PREPARED ) {
 keyblock_cache . state = KEYBLOCK_CACHE_FILLED ;
 keyblock_cache . sigstatus = sigstatus ;
 keyblock_cache . iobuf = iobuf ;
 keyblock_cache . pk_no = pk_no ;
 keyblock_cache . uid_no = uid_no ;
 }
 else {
 xfree ( sigstatus ) ;
 iobuf_close ( iobuf ) ;
 }
 }
 }
 break ;
 }
 if ( keyblock_cache . state != KEYBLOCK_CACHE_FILLED ) keyblock_cache_clear ( ) ;
 return err ;
 }