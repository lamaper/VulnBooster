static int rsvp_hostlist_packet ( void * pit , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * vip ) {
 conv_hash_t * hash = ( conv_hash_t * ) pit ;
 const rsvp_conversation_info * rsvph = ( const rsvp_conversation_info * ) vip ;
 add_hostlist_table_data ( hash , & rsvph -> source , 0 , TRUE , 1 , pinfo -> fd -> pkt_len , & rsvp_host_dissector_info , PT_NONE ) ;
 add_hostlist_table_data ( hash , & rsvph -> destination , 0 , FALSE , 1 , pinfo -> fd -> pkt_len , & rsvp_host_dissector_info , PT_NONE ) ;
 return 1 ;
 }