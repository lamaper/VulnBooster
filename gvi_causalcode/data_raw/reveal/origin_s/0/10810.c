TSVConn TSHttpConnect ( sockaddr const * addr ) {
 return TSHttpConnectWithPluginId ( addr , "plugin" , 0 ) ;
 }