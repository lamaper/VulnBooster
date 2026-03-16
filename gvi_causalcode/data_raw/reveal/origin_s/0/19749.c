static SocketAddress * nbd_build_socket_address ( const char * sockpath , const char * bindto , const char * port ) {
 SocketAddress * saddr ;
 saddr = g_new0 ( SocketAddress , 1 ) ;
 if ( sockpath ) {
 saddr -> type = SOCKET_ADDRESS_TYPE_UNIX ;
 saddr -> u . q_unix . path = g_strdup ( sockpath ) ;
 }
 else {
 InetSocketAddress * inet ;
 saddr -> type = SOCKET_ADDRESS_TYPE_INET ;
 inet = & saddr -> u . inet ;
 inet -> host = g_strdup ( bindto ) ;
 if ( port ) {
 inet -> port = g_strdup ( port ) ;
 }
 else {
 inet -> port = g_strdup_printf ( "%d" , NBD_DEFAULT_PORT ) ;
 }
 }
 return saddr ;
 }