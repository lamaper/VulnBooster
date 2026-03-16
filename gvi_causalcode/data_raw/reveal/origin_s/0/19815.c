static void rtp_dyn_payload_value_destroy ( gpointer data ) {
 encoding_name_and_rate_t * encoding_name_and_rate_pt = ( encoding_name_and_rate_t * ) data ;
 wmem_free ( wmem_file_scope ( ) , encoding_name_and_rate_pt -> encoding_name ) ;
 wmem_free ( wmem_file_scope ( ) , encoding_name_and_rate_pt ) ;
 }