static void set_upstream_server_address ( ngx_http_upstream_t * upstream , ngx_http_upstream_conf_t * upstream_config ) {
 ngx_http_upstream_server_t * servers = upstream_config -> upstream -> servers -> elts ;
 ngx_addr_t * address = & servers [ 0 ] . addrs [ 0 ] ;
 const char * request_socket_filename ;
 unsigned int request_socket_filename_len ;
 struct sockaddr_un * sockaddr ;
 if ( address -> name . data == pp_placeholder_upstream_address . data ) {
 sockaddr = ( struct sockaddr_un * ) address -> sockaddr ;
 request_socket_filename = pp_agents_starter_get_request_socket_filename ( pp_agents_starter , & request_socket_filename_len ) ;
 address -> name . data = ( u_char * ) request_socket_filename ;
 address -> name . len = request_socket_filename_len ;
 strncpy ( sockaddr -> sun_path , request_socket_filename , sizeof ( sockaddr -> sun_path ) ) ;
 sockaddr -> sun_path [ sizeof ( sockaddr -> sun_path ) - 1 ] = '\0' ;
 }
 }