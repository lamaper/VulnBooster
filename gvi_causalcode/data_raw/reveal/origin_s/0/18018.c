int keyring_delete_keyblock ( KEYRING_HANDLE hd ) {
 int rc ;
 if ( ! hd -> found . kr ) return - 1 ;
 if ( hd -> found . kr -> read_only ) return gpg_error ( GPG_ERR_EACCES ) ;
 if ( ! hd -> found . n_packets ) {
 rc = keyring_get_keyblock ( hd , NULL ) ;
 if ( rc ) {
 log_error ( "re-reading keyblock failed: %s\n" , gpg_strerror ( rc ) ) ;
 return rc ;
 }
 if ( ! hd -> found . n_packets ) BUG ( ) ;
 }
 iobuf_close ( hd -> current . iobuf ) ;
 hd -> current . iobuf = NULL ;
 rc = do_copy ( 2 , hd -> found . kr -> fname , NULL , hd -> found . offset , hd -> found . n_packets ) ;
 if ( ! rc ) {
 hd -> found . kr = NULL ;
 hd -> found . offset = 0 ;
 }
 return rc ;
 }