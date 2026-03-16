static void h245_init ( void ) {
 if ( h245_pending_olc_reqs ) g_hash_table_destroy ( h245_pending_olc_reqs ) ;
 h245_pending_olc_reqs = g_hash_table_new ( g_str_hash , g_str_equal ) ;
 h223_lc_init ( ) ;
 }