static void h225_cleanup_routine ( void ) {
 int i ;
 for ( i = 0 ;
 i < 7 ;
 i ++ ) {
 g_hash_table_destroy ( ras_calls [ i ] ) ;
 }
 }