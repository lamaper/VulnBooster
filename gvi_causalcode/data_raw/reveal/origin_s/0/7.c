TSReturnCode TSPortDescriptorAccept ( TSPortDescriptor descp , TSCont contp ) {
 Action * action = nullptr ;
 HttpProxyPort * port = ( HttpProxyPort * ) descp ;
 NetProcessor : : AcceptOptions net ( make_net_accept_options ( port , - 1 ) ) ;
 if ( port -> isSSL ( ) ) {
 action = sslNetProcessor . main_accept ( ( INKContInternal * ) contp , port -> m_fd , net ) ;
 }
 else {
 action = netProcessor . main_accept ( ( INKContInternal * ) contp , port -> m_fd , net ) ;
 }
 return action ? TS_SUCCESS : TS_ERROR ;
 }