static gboolean rtp_dyn_payloads_table_steal_func ( gpointer key _U_ , gpointer value , gpointer user_data _U_ ) {
 rtp_dyn_payload_t * rtp_dyn_payload = ( rtp_dyn_payload_t * ) value ;

 DINDENT ( ) ;
 rtp_dump_dyn_payload ( rtp_dyn_payload ) ;
 DENDENT ( ) ;

 g_error ( "rtp_dyn_payload cannot be free'd because it should already have been!\n" ) ;
 }
 else if ( rtp_dyn_payload -> table ) {
 g_hash_table_steal_all ( rtp_dyn_payload -> table ) ;
 g_hash_table_destroy ( rtp_dyn_payload -> table ) ;
 }
 return TRUE ;
 }