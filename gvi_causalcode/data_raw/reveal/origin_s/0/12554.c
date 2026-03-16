int keyring_update_keyblock ( KEYRING_HANDLE hd , KBNODE kb ) {
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
 rc = do_copy ( 3 , hd -> found . kr -> fname , kb , hd -> found . offset , hd -> found . n_packets ) ;
 if ( ! rc ) {
 if ( kr_offtbl ) {
 update_offset_hash_table_from_kb ( kr_offtbl , kb , 0 ) ;
 }
 hd -> found . kr = NULL ;
 hd -> found . offset = 0 ;
 }
 return rc ;
 }