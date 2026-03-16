void proto_reg_handoff_diameter ( void ) {
 static gboolean Initialized = FALSE ;
 static range_t * diameter_tcp_port_range ;
 static range_t * diameter_sctp_port_range ;
 static range_t * diameter_udp_port_range ;
 if ( ! Initialized ) {
 diameter_sctp_handle = find_dissector ( "diameter" ) ;
 diameter_tcp_handle = new_create_dissector_handle ( dissect_diameter_tcp , proto_diameter ) ;
 diameter_udp_handle = new_create_dissector_handle ( dissect_diameter , proto_diameter ) ;
 data_handle = find_dissector ( "data" ) ;
 eap_handle = find_dissector ( "eap" ) ;
 dissector_add_uint ( "sctp.ppi" , DIAMETER_PROTOCOL_ID , diameter_sctp_handle ) ;
 dissector_add_uint ( "diameter.base" , 1 , new_create_dissector_handle ( dissect_diameter_user_name , proto_diameter ) ) ;
 dissector_add_uint ( "diameter.base" , 97 , new_create_dissector_handle ( dissect_diameter_base_framed_ipv6_prefix , proto_diameter ) ) ;
 dissector_add_uint ( "diameter.base" , 265 , new_create_dissector_handle ( dissect_diameter_vendor_id , proto_diameter ) ) ;
 dissector_add_uint ( "diameter.base" , 266 , new_create_dissector_handle ( dissect_diameter_vendor_id , proto_diameter ) ) ;
 dissector_add_uint ( "diameter.base" , 443 , new_create_dissector_handle ( dissect_diameter_subscription_id , proto_diameter ) ) ;
 dissector_add_uint ( "diameter.base" , 450 , new_create_dissector_handle ( dissect_diameter_subscription_id_type , proto_diameter ) ) ;
 dissector_add_uint ( "diameter.base" , 444 , new_create_dissector_handle ( dissect_diameter_subscription_id_data , proto_diameter ) ) ;
 dissector_add_uint ( "diameter.base" , 462 , new_create_dissector_handle ( dissect_diameter_eap_payload , proto_diameter ) ) ;
 dissector_add_uint ( "diameter.base" , 463 , new_create_dissector_handle ( dissect_diameter_eap_payload , proto_diameter ) ) ;
 dissector_add_uint ( "diameter.vnd_exp_res" , VENDOR_THE3GPP2 , new_create_dissector_handle ( dissect_diameter_3gpp2_exp_res , proto_diameter ) ) ;
 Initialized = TRUE ;
 }
 else {
 dissector_delete_uint_range ( "tcp.port" , diameter_tcp_port_range , diameter_tcp_handle ) ;
 dissector_delete_uint_range ( "sctp.port" , diameter_sctp_port_range , diameter_sctp_handle ) ;
 dissector_delete_uint_range ( "udp.port" , diameter_udp_port_range , diameter_udp_handle ) ;
 g_free ( diameter_tcp_port_range ) ;
 g_free ( diameter_sctp_port_range ) ;
 g_free ( diameter_udp_port_range ) ;
 }
 diameter_tcp_port_range = range_copy ( global_diameter_tcp_port_range ) ;
 diameter_sctp_port_range = range_copy ( global_diameter_sctp_port_range ) ;
 diameter_udp_port_range = range_copy ( global_diameter_udp_port_range ) ;
 dissector_add_uint_range ( "tcp.port" , diameter_tcp_port_range , diameter_tcp_handle ) ;
 dissector_add_uint_range ( "sctp.port" , diameter_sctp_port_range , diameter_sctp_handle ) ;
 dissector_add_uint_range ( "udp.port" , diameter_udp_port_range , diameter_udp_handle ) ;
 exported_pdu_tap = find_tap_id ( EXPORT_PDU_TAP_NAME_LAYER_7 ) ;
 }