static int stp_print_config_bpdu ( netdissect_options * ndo , const struct stp_bpdu_ * stp_bpdu , u_int length ) {
 ND_TCHECK ( stp_bpdu -> flags ) ;
 ND_PRINT ( ( ndo , ", Flags [%s]" , bittok2str ( stp_bpdu_flag_values , "none" , stp_bpdu -> flags ) ) ) ;
 ND_TCHECK ( stp_bpdu -> port_id ) ;
 ND_PRINT ( ( ndo , ", bridge-id %s.%04x, length %u" , stp_print_bridge_id ( ( const u_char * ) & stp_bpdu -> bridge_id ) , EXTRACT_16BITS ( & stp_bpdu -> port_id ) , length ) ) ;
 if ( ! ndo -> ndo_vflag ) {
 return 1 ;
 }
 ND_TCHECK ( stp_bpdu -> forward_delay ) ;
 ND_PRINT ( ( ndo , "\n\tmessage-age %.2fs, max-age %.2fs" ", hello-time %.2fs, forwarding-delay %.2fs" , ( float ) EXTRACT_16BITS ( & stp_bpdu -> message_age ) / STP_TIME_BASE , ( float ) EXTRACT_16BITS ( & stp_bpdu -> max_age ) / STP_TIME_BASE , ( float ) EXTRACT_16BITS ( & stp_bpdu -> hello_time ) / STP_TIME_BASE , ( float ) EXTRACT_16BITS ( & stp_bpdu -> forward_delay ) / STP_TIME_BASE ) ) ;
 ND_PRINT ( ( ndo , "\n\troot-id %s, root-pathcost %u" , stp_print_bridge_id ( ( const u_char * ) & stp_bpdu -> root_id ) , EXTRACT_32BITS ( & stp_bpdu -> root_path_cost ) ) ) ;
 if ( stp_bpdu -> protocol_version == STP_PROTO_RAPID ) {
 ND_PRINT ( ( ndo , ", port-role %s" , tok2str ( rstp_obj_port_role_values , "Unknown" , RSTP_EXTRACT_PORT_ROLE ( stp_bpdu -> flags ) ) ) ) ;
 }
 return 1 ;
 trunc : return 0 ;
 }