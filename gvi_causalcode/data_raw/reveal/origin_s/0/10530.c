static void update_unicast_addr ( unicast_addr_t * req_addr , unicast_addr_t * ack_addr ) {
 if ( ack_addr -> addr . type != AT_NONE && ack_addr -> port != 0 ) {
 memcpy ( req_addr -> addr_buf , ack_addr -> addr_buf , sizeof ( req_addr -> addr_buf ) ) ;
 SET_ADDRESS ( & req_addr -> addr , ack_addr -> addr . type , ack_addr -> addr . len , req_addr -> addr_buf ) ;
 req_addr -> port = ack_addr -> port ;
 }
 }