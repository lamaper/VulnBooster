static const SSL_METHOD * ssl23_get_server_method ( int ver ) {



 else if ( ver == TLS1_1_VERSION ) return ( TLSv1_1_server_method ( ) ) ;
 else if ( ver == TLS1_2_VERSION ) return ( TLSv1_2_server_method ( ) ) ;
 else return ( NULL ) ;
 }