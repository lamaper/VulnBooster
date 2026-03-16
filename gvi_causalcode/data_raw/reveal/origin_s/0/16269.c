static void fix_peer_address ( ngx_http_request_t * r ) {
 ngx_http_upstream_rr_peer_data_t * rrp ;
 ngx_http_upstream_rr_peers_t * peers ;
 ngx_http_upstream_rr_peer_t * peer ;
 unsigned int peer_index ;
 const char * request_socket_filename ;
 unsigned int request_socket_filename_len ;
 if ( r -> upstream -> peer . get != ngx_http_upstream_get_round_robin_peer ) {
 return ;
 }
 rrp = r -> upstream -> peer . data ;
 peers = rrp -> peers ;
 request_socket_filename = pp_agents_starter_get_request_socket_filename ( pp_agents_starter , & request_socket_filename_len ) ;
 while ( peers != NULL ) {
 if ( peers -> name ) {
 if ( peers -> name -> data == ( u_char * ) request_socket_filename ) {
 return ;
 }
 peers -> name -> data = ( u_char * ) request_socket_filename ;
 peers -> name -> len = request_socket_filename_len ;
 }
 peer_index = 0 ;
 while ( 1 ) {
 peer = & peers -> peer [ peer_index ] ;
 peer -> name . data = ( u_char * ) request_socket_filename ;
 peer -> name . len = request_socket_filename_len ;
 if ( peer -> down ) {
 peer_index ++ ;
 }
 else {
 break ;
 }
 }
 peers = peers -> next ;
 }
 }