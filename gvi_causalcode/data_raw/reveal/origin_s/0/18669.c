TSAction TSNetConnect ( TSCont contp , sockaddr const * addr ) {
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( ats_is_ip ( addr ) ) ;
 HttpConfigParams * http_config_param = HttpConfig : : acquire ( ) ;
 NetVCOptions opt ;
 if ( http_config_param ) {
 opt . set_sock_param ( http_config_param -> oride . sock_recv_buffer_size_out , http_config_param -> oride . sock_send_buffer_size_out , http_config_param -> oride . sock_option_flag_out , http_config_param -> oride . sock_packet_mark_out , http_config_param -> oride . sock_packet_tos_out ) ;
 HttpConfig : : release ( http_config_param ) ;
 }
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 return reinterpret_cast < TSAction > ( netProcessor . connect_re ( reinterpret_cast < INKContInternal * > ( contp ) , addr , & opt ) ) ;
 }