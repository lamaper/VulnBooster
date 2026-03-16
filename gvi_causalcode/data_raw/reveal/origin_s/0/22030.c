TSAction TSNetConnectTransparent ( TSCont contp , sockaddr const * client_addr , sockaddr const * server_addr ) {
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( ats_is_ip ( server_addr ) ) ;
 sdk_assert ( ats_ip_are_compatible ( client_addr , server_addr ) ) ;
 NetVCOptions opt ;
 opt . addr_binding = NetVCOptions : : FOREIGN_ADDR ;
 opt . local_ip . assign ( client_addr ) ;
 opt . local_port = ats_ip_port_host_order ( client_addr ) ;
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 return reinterpret_cast < TSAction > ( netProcessor . connect_re ( reinterpret_cast < INKContInternal * > ( contp ) , server_addr , & opt ) ) ;
 }