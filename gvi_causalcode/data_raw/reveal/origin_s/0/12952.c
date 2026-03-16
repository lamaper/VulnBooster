static void oid_free_cb ( void * r ) {
 oid_user_t * u = ( oid_user_t * ) r ;
 g_free ( u -> oid ) ;
 g_free ( u -> name ) ;
 }