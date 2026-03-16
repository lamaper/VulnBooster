static ID2 * scope_chunk_get ( Operation * op ) {
 struct mdb_info * mdb = ( struct mdb_info * ) op -> o_bd -> be_private ;
 ID2 * ret = NULL ;
 ldap_pvt_thread_pool_getkey ( op -> o_threadctx , ( void * ) scope_chunk_get , ( void * ) & ret , NULL ) ;
 if ( ! ret ) {
 ret = ch_malloc ( MDB_IDL_UM_SIZE * sizeof ( ID2 ) ) ;
 }
 else {
 void * r2 = ret [ 0 ] . mval . mv_data ;
 ldap_pvt_thread_pool_setkey ( op -> o_threadctx , ( void * ) scope_chunk_get , r2 , scope_chunk_free , NULL , NULL ) ;
 }
 return ret ;
 }