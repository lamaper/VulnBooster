TSReturnCode TSPluginDescriptorAccept ( TSCont contp ) {
 Action * action = nullptr ;
 HttpProxyPort : : Group & proxy_ports = HttpProxyPort : : global ( ) ;
 for ( int i = 0 , n = proxy_ports . length ( ) ;
 i < n ;
 ++ i ) {
 HttpProxyPort & port = proxy_ports [ i ] ;
 if ( port . isPlugin ( ) ) {
 NetProcessor : : AcceptOptions net ( make_net_accept_options ( & port , - 1 ) ) ;
 action = netProcessor . main_accept ( ( INKContInternal * ) contp , port . m_fd , net ) ;
 }
 }
 return action ? TS_SUCCESS : TS_ERROR ;
 }