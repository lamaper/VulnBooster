static void ber_update_oids ( void ) {
 guint i ;
 for ( i = 0 ;
 i < num_oid_users ;
 i ++ ) register_ber_oid_syntax ( oid_users [ i ] . oid , oid_users [ i ] . name , oid_users [ i ] . syntax ) ;
 }