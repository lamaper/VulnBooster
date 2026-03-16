void proto_reg_handoff_AllJoyn ( void ) {
 static gboolean initialized = FALSE ;
 static dissector_handle_t alljoyn_handle_ns ;
 static dissector_handle_t alljoyn_handle_ardp ;
 if ( ! initialized ) {
 alljoyn_handle_ns = new_create_dissector_handle ( dissect_AllJoyn_name_server , proto_AllJoyn_ns ) ;
 alljoyn_handle_ardp = new_create_dissector_handle ( dissect_AllJoyn_ardp , proto_AllJoyn_ardp ) ;
 }
 else {
 dissector_delete_uint ( "udp.port" , name_server_port , alljoyn_handle_ns ) ;
 dissector_delete_uint ( "tcp.port" , name_server_port , alljoyn_handle_ns ) ;
 dissector_delete_uint ( "udp.port" , message_port , alljoyn_handle_ardp ) ;
 dissector_delete_uint ( "tcp.port" , message_port , alljoyn_handle_ardp ) ;
 }
 dissector_add_uint ( "udp.port" , name_server_port , alljoyn_handle_ns ) ;
 dissector_add_uint ( "tcp.port" , name_server_port , alljoyn_handle_ns ) ;
 dissector_add_uint ( "udp.port" , message_port , alljoyn_handle_ardp ) ;
 dissector_add_uint ( "tcp.port" , message_port , alljoyn_handle_ardp ) ;
 }