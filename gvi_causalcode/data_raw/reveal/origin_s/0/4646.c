static void * search_stack ( Operation * op ) {
 struct mdb_info * mdb = ( struct mdb_info * ) op -> o_bd -> be_private ;
 void * ret = NULL ;
 if ( op -> o_threadctx ) {
 ldap_pvt_thread_pool_getkey ( op -> o_threadctx , ( void * ) search_stack , & ret , NULL ) ;
 }
 else {
 ret = mdb -> mi_search_stack ;
 }
 if ( ! ret ) {
 ret = ch_malloc ( mdb -> mi_search_stack_depth * MDB_IDL_UM_SIZE * sizeof ( ID ) ) ;
 if ( op -> o_threadctx ) {
 ldap_pvt_thread_pool_setkey ( op -> o_threadctx , ( void * ) search_stack , ret , search_stack_free , NULL , NULL ) ;
 }
 else {
 mdb -> mi_search_stack = ret ;
 }
 }
 return ret ;
 }