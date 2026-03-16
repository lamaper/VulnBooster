static void rtp_dyn_payloads_init ( void ) {
 if ( rtp_dyn_payloads == NULL ) {
 rtp_dyn_payloads = g_hash_table_new ( NULL , NULL ) ;
 wmem_register_callback ( wmem_file_scope ( ) , wmem_rtp_dyn_payload_destroy_cb , NULL ) ;
 }
 }