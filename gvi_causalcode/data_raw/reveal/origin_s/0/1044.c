static void h225_init_routine ( void ) {
 int i ;
 for ( i = 0 ;
 i < 7 ;
 i ++ ) {
 ras_calls [ i ] = g_hash_table_new ( h225ras_call_hash , h225ras_call_equal ) ;
 }
 }