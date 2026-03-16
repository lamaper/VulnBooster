rtp_dyn_payload_t * rtp_dyn_payload_new ( void ) {
 rtp_dyn_payload_t * rtp_dyn_payload = wmem_new ( wmem_file_scope ( ) , rtp_dyn_payload_t ) ;
 rtp_dyn_payload -> table = g_hash_table_new_full ( NULL , NULL , NULL , rtp_dyn_payload_value_destroy ) ;
 rtp_dyn_payload -> ref_count = 1 ;
 g_hash_table_insert ( rtp_dyn_payloads , rtp_dyn_payload , rtp_dyn_payload ) ;
 return rtp_dyn_payload ;
 }