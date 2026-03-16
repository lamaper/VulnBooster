static int mdb_waitfixup ( Operation * op , ww_ctx * ww , MDB_cursor * mci , MDB_cursor * mcd , IdScopes * isc ) {
 MDB_val key ;
 int rc = 0 ;
 ww -> flag = 0 ;
 mdb_txn_renew ( ww -> txn ) ;
 mdb_cursor_renew ( ww -> txn , mci ) ;
 mdb_cursor_renew ( ww -> txn , mcd ) ;
 key . mv_size = sizeof ( ID ) ;
 if ( ww -> mcd ) {
 MDB_val data ;
 if ( isc -> numrdns ) mdb_dn2id_wrestore ( op , isc ) ;
 key . mv_data = & ww -> key ;
 data = ww -> data ;
 rc = mdb_cursor_get ( mcd , & key , & data , MDB_GET_BOTH ) ;
 if ( rc == MDB_NOTFOUND ) {
 data = ww -> data ;
 rc = mdb_cursor_get ( mcd , & key , & data , MDB_GET_BOTH_RANGE ) ;
 if ( rc == MDB_SUCCESS ) mdb_cursor_get ( mcd , & key , & data , MDB_PREV_DUP ) ;
 else rc = LDAP_BUSY ;
 }
 else if ( rc ) {
 rc = LDAP_OTHER ;
 }
 op -> o_tmpfree ( ww -> data . mv_data , op -> o_tmpmemctx ) ;
 ww -> data . mv_data = NULL ;
 }
 else if ( isc -> scopes [ 0 ] . mid > 1 ) {
 int i ;
 for ( i = 1 ;
 i < isc -> scopes [ 0 ] . mid ;
 i ++ ) {
 if ( ! isc -> scopes [ i ] . mval . mv_data ) continue ;
 key . mv_data = & isc -> scopes [ i ] . mid ;
 mdb_cursor_get ( mcd , & key , & isc -> scopes [ i ] . mval , MDB_SET ) ;
 }
 }
 return rc ;
 }