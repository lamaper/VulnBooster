TSVConn TSVConnFdCreate ( int fd ) {
 UnixNetVConnection * vc ;
 if ( unlikely ( fd == NO_FD ) ) {
 return nullptr ;
 }
 vc = ( UnixNetVConnection * ) netProcessor . allocate_vc ( this_ethread ( ) ) ;
 if ( vc == nullptr ) {
 return nullptr ;
 }
 vc -> action_ = & a ;
 vc -> id = net_next_connection_number ( ) ;
 vc -> submit_time = Thread : : get_hrtime ( ) ;
 vc -> set_is_transparent ( false ) ;
 vc -> mutex = new_ProxyMutex ( ) ;
 vc -> set_context ( NET_VCONNECTION_OUT ) ;
 if ( vc -> connectUp ( this_ethread ( ) , fd ) != CONNECT_SUCCESS ) {
 return nullptr ;
 }
 NET_SUM_GLOBAL_DYN_STAT ( net_connections_currently_open_stat , 1 ) ;
 return reinterpret_cast < TSVConn > ( vc ) ;
 }