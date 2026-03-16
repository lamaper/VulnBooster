static void mac_init ( void ) {
 mac_is_sdus = g_hash_table_new_full ( mac_is_channel_hash , mac_is_channel_equal , NULL , mac_is_sdus_hash_destroy ) ;
 mac_is_fragments = g_hash_table_new_full ( mac_is_channel_hash , mac_is_channel_equal , NULL , NULL ) ;
 if ( global_mac_tsn_size == MAC_TSN_6BITS ) {
 MAX_TSN = 64 ;
 mac_tsn_size = 6 ;
 }
 else {
 MAX_TSN = 16384 ;
 mac_tsn_size = 14 ;
 }
 }