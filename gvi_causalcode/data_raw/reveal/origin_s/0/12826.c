static void h223_lc_init_dir ( int dir ) {
 if ( h223_pending_olc_reqs [ dir ] ) g_hash_table_destroy ( h223_pending_olc_reqs [ dir ] ) ;
 h223_pending_olc_reqs [ dir ] = g_hash_table_new ( g_direct_hash , g_direct_equal ) ;
 }