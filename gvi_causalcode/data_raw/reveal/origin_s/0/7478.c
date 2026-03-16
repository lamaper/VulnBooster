static int sua_calls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * prot_info ) {
 sccp_payload_values = sua_co_class_type_acro_values ;
 return sccp_calls ( pinfo , prot_info ) ;
 }