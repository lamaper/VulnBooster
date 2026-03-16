TSVConn TSHttpConnectWithPluginId ( sockaddr const * addr , const char * tag , int64_t id ) {
 sdk_assert ( addr ) ;
 sdk_assert ( ats_is_ip ( addr ) ) ;
 sdk_assert ( ats_ip_port_cast ( addr ) ) ;
 if ( plugin_http_accept ) {
 PluginVCCore * new_pvc = PluginVCCore : : alloc ( plugin_http_accept ) ;
 new_pvc -> set_active_addr ( addr ) ;
 new_pvc -> set_plugin_id ( id ) ;
 new_pvc -> set_plugin_tag ( tag ) ;
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