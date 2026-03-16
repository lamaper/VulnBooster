TSVConn TSHttpConnectTransparent ( sockaddr const * client_addr , sockaddr const * server_addr ) {
 sdk_assert ( ats_is_ip ( client_addr ) ) ;
 sdk_assert ( ats_is_ip ( server_addr ) ) ;
 sdk_assert ( ! ats_is_ip_any ( client_addr ) ) ;
 sdk_assert ( ats_ip_port_cast ( client_addr ) ) ;
 sdk_assert ( ! ats_is_ip_any ( server_addr ) ) ;
 sdk_assert ( ats_ip_port_cast ( server_addr ) ) ;
 if ( plugin_http_transparent_accept ) {
 PluginVCCore * new_pvc = PluginVCCore : : alloc ( plugin_http_transparent_accept ) ;
 new_pvc -> set_active_addr ( client_addr ) ;
 new_pvc -> set_passive_addr ( server_addr ) ;
 new_pvc -> set_transparent ( true , true ) ;
 PluginVC * return_vc = new_pvc -> connect ( ) ;
 if ( return_vc != nullptr ) {
 PluginVC * other_side = return_vc -> get_other_side ( ) ;
 if ( other_side != nullptr ) {
 other_side -> set_is_internal_request ( true ) ;
 }
 }
 return reinterpret_cast < TSVConn > ( return_vc ) ;
 }
 return nullptr ;
 }