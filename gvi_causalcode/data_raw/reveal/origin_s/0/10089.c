void proto_reg_handoff_rsvp ( void ) {
 dissector_handle_t rsvp_handle , rsvpe2ei_handle ;
 rsvp_handle = new_create_dissector_handle ( dissect_rsvp , proto_rsvp ) ;
 rsvpe2ei_handle = new_create_dissector_handle ( dissect_rsvp_e2ei , proto_rsvp_e2e1 ) ;
 dissector_add_uint ( "ip.proto" , IP_PROTO_RSVP , rsvp_handle ) ;
 dissector_add_uint ( "ip.proto" , IP_PROTO_RSVPE2EI , rsvpe2ei_handle ) ;
 dissector_add_uint ( "udp.port" , UDP_PORT_PRSVP , rsvp_handle ) ;
 rsvp_tap = register_tap ( "rsvp" ) ;
 }