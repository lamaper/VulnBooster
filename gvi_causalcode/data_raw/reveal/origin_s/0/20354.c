static int http_getsock_do ( struct connectdata * conn , curl_socket_t * socks , int numsocks ) {
 ( void ) numsocks ;
 socks [ 0 ] = conn -> sock [ FIRSTSOCKET ] ;
 return GETSOCK_WRITESOCK ( 0 ) ;
 }