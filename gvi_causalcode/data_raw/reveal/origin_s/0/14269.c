int keyring_insert_keyblock ( KEYRING_HANDLE hd , KBNODE kb ) {
 int rc ;
 const char * fname ;
 if ( ! hd ) fname = NULL ;
 else if ( hd -> found . kr ) {
 fname = hd -> found . kr -> fname ;
 if ( hd -> found . kr -> read_only ) return gpg_error ( GPG_ERR_EACCES ) ;
 }
 else if ( hd -> current . kr ) {
 fname = hd -> current . kr -> fname ;
 if ( hd -> current . kr -> read_only ) return gpg_error ( GPG_ERR_EACCES ) ;
 }
 else fname = hd -> resource ? hd -> resource -> fname : NULL ;
 if ( ! fname ) return GPG_ERR_GENERAL ;
 iobuf_close ( hd -> current . iobuf ) ;
 hd -> current . iobuf = NULL ;
 rc = do_copy ( 1 , fname , kb , 0 , 0 ) ;
 if ( ! rc && kr_offtbl ) {
 update_offset_hash_table_from_kb ( kr_offtbl , kb , 0 ) ;
 }
 return rc ;
 }