void grant_free ( void ) {
 DBUG_ENTER ( "grant_free" ) ;
 hash_free ( & column_priv_hash ) ;
 hash_free ( & proc_priv_hash ) ;
 hash_free ( & func_priv_hash ) ;
 free_root ( & memex , MYF ( 0 ) ) ;
 DBUG_VOID_RETURN ;
 }