static int sccp_calls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * prot_info ) {
 sccp_payload_values = sccp_message_type_acro_values ;
 return sccp_calls ( pinfo , prot_info ) ;
 }