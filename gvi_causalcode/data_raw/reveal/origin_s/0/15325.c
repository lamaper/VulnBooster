static void iax2_populate_pinfo_from_packet_data ( packet_info * pinfo , const iax_packet_data * p ) {
 if ( p -> call_data != NULL ) {
 pinfo -> p2p_dir = p -> reversed ? P2P_DIR_RECV : P2P_DIR_SENT ;
 col_set_str ( pinfo -> cinfo , COL_IF_DIR , p -> reversed ? "rev" : "fwd" ) ;
 }
 }