static void * oid_copy_cb ( void * dest , const void * orig , size_t len _U_ ) {
 oid_user_t * u = ( oid_user_t * ) dest ;
 const oid_user_t * o = ( const oid_user_t * ) orig ;
 u -> oid = g_strdup ( o -> oid ) ;
 u -> name = g_strdup ( o -> name ) ;
 u -> syntax = o -> syntax ;
 return dest ;
 }