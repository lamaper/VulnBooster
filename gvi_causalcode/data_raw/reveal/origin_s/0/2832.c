void rtp_dyn_payload_free ( rtp_dyn_payload_t * rtp_dyn_payload ) {
 if ( ! rtp_dyn_payload ) return ;
 if ( rtp_dyn_payload -> ref_count > 0 ) -- ( rtp_dyn_payload -> ref_count ) ;
 if ( rtp_dyn_payload -> ref_count == 0 ) {

 DINDENT ( ) ;
 rtp_dump_dyn_payload ( rtp_dyn_payload ) ;
 DENDENT ( ) ;

 if ( ! g_hash_table_remove ( rtp_dyn_payloads , rtp_dyn_payload ) ) {
 g_error ( "rtp_dyn_payload not found in rtp_dyn_payloads table to remove!" ) ;
 }
 if ( rtp_dyn_payload -> table ) g_hash_table_destroy ( rtp_dyn_payload -> table ) ;
 wmem_free ( wmem_file_scope ( ) , rtp_dyn_payload ) ;
 }
 }