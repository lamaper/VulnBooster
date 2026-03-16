void proto_reg_handoff_dns ( void ) {
 dissector_handle_t dns_sctp_handle ;
 dissector_handle_t mdns_udp_handle ;
 dissector_handle_t llmnr_udp_handle ;
 static range_t * dns_tcp_port_range ;
 static range_t * dns_udp_port_range ;
 static gboolean Initialized = FALSE ;
 if ( ! Initialized ) {
 dns_udp_handle = create_dissector_handle ( dissect_dns_udp , proto_dns ) ;
 dns_tcp_handle = new_create_dissector_handle ( dissect_dns_tcp , proto_dns ) ;
 stats_tree_register ( "dns" , "dns" , "DNS" , 0 , dns_stats_tree_packet , dns_stats_tree_init , NULL ) ;
 Initialized = TRUE ;
 }
 else {
 dissector_delete_uint_range ( "tcp.port" , dns_tcp_port_range , dns_tcp_handle ) ;
 dissector_delete_uint_range ( "udp.port" , dns_udp_port_range , dns_udp_handle ) ;
 g_free ( dns_tcp_port_range ) ;
 g_free ( dns_udp_port_range ) ;
 }
 dns_tcp_port_range = range_copy ( global_dns_tcp_port_range ) ;
 dns_udp_port_range = range_copy ( global_dns_udp_port_range ) ;
 dissector_add_uint_range ( "tcp.port" , dns_tcp_port_range , dns_tcp_handle ) ;
 dissector_add_uint_range ( "udp.port" , dns_udp_port_range , dns_udp_handle ) ;
 dns_sctp_handle = create_dissector_handle ( dissect_dns_sctp , proto_dns ) ;
 mdns_udp_handle = create_dissector_handle ( dissect_mdns_udp , proto_dns ) ;
 llmnr_udp_handle = create_dissector_handle ( dissect_llmnr_udp , proto_dns ) ;
 dissector_add_uint ( "udp.port" , UDP_PORT_MDNS , mdns_udp_handle ) ;
 dissector_add_uint ( "tcp.port" , TCP_PORT_MDNS , dns_tcp_handle ) ;
 dissector_add_uint ( "udp.port" , UDP_PORT_LLMNR , llmnr_udp_handle ) ;
 dissector_add_uint ( "sctp.port" , SCTP_PORT_DNS , dns_sctp_handle ) ;


 ntlmssp_handle = find_dissector ( "ntlmssp" ) ;
 }