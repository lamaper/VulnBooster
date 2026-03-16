static void scope_chunk_ret ( Operation * op , ID2 * scopes ) {
 struct mdb_info * mdb = ( struct mdb_info * ) op -> o_bd -> be_private ;
 void * ret = NULL ;
 ldap_pvt_thread_pool_getkey ( op -> o_threadctx , ( void * ) scope_chunk_get , & ret , NULL ) ;
 scopes [ 0 ] . mval . mv_data = ret ;
 ldap_pvt_thread_pool_setkey ( op -> o_threadctx , ( void * ) scope_chunk_get , ( void * ) scopes , scope_chunk_free , NULL , NULL ) ;
 }