static void mac_cleanup ( void ) {
 g_hash_table_destroy ( mac_is_sdus ) ;
 g_hash_table_destroy ( mac_is_fragments ) ;
 }