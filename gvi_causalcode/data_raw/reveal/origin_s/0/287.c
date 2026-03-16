static int tunnel ( int tun_fd , int dns_fd , int bind_fd , int max_idle_time ) {
 struct timeval tv ;
 fd_set fds ;
 int i ;
 int userid ;
 time_t last_action = time ( NULL ) ;
 while ( running ) {
 int maxfd ;
 tv . tv_sec = 10 ;
 tv . tv_usec = 0 ;
 for ( userid = 0 ;
 userid < created_users ;
 userid ++ ) {
 if ( users [ userid ] . active && ! users [ userid ] . disabled && users [ userid ] . last_pkt + 60 > time ( NULL ) ) {
 users [ userid ] . q_sendrealsoon_new = 0 ;
 if ( users [ userid ] . q_sendrealsoon . id != 0 ) {
 tv . tv_sec = 0 ;
 tv . tv_usec = 20000 ;
 }
 }
 }
 FD_ZERO ( & fds ) ;
 FD_SET ( dns_fd , & fds ) ;
 maxfd = dns_fd ;
 if ( bind_fd ) {
 FD_SET ( bind_fd , & fds ) ;
 maxfd = MAX ( bind_fd , maxfd ) ;
 }
 if ( ! all_users_waiting_to_send ( ) ) {
 FD_SET ( tun_fd , & fds ) ;
 maxfd = MAX ( tun_fd , maxfd ) ;
 }
 i = select ( maxfd + 1 , & fds , NULL , NULL , & tv ) ;
 if ( i < 0 ) {
 if ( running ) warn ( "select" ) ;
 return 1 ;
 }
 if ( i == 0 ) {
 if ( max_idle_time ) {
 if ( last_action + max_idle_time < time ( NULL ) ) {
 for ( userid = 0 ;
 userid < created_users ;
 userid ++ ) {
 last_action = ( users [ userid ] . last_pkt > last_action ) ? users [ userid ] . last_pkt : last_action ;
 }
 if ( last_action + max_idle_time < time ( NULL ) ) {
 fprintf ( stderr , "Idling since too long, shutting down...\n" ) ;
 running = 0 ;
 }
 }
 }
 }
 else {
 if ( FD_ISSET ( tun_fd , & fds ) ) {
 tunnel_tun ( tun_fd , dns_fd ) ;
 }
 if ( FD_ISSET ( dns_fd , & fds ) ) {
 tunnel_dns ( tun_fd , dns_fd , bind_fd ) ;
 }
 if ( FD_ISSET ( bind_fd , & fds ) ) {
 tunnel_bind ( bind_fd , dns_fd ) ;
 }
 }
 for ( userid = 0 ;
 userid < created_users ;
 userid ++ ) if ( users [ userid ] . active && ! users [ userid ] . disabled && users [ userid ] . last_pkt + 60 > time ( NULL ) && users [ userid ] . q_sendrealsoon . id != 0 && users [ userid ] . conn == CONN_DNS_NULL && ! users [ userid ] . q_sendrealsoon_new ) send_chunk_or_dataless ( dns_fd , userid , & users [ userid ] . q_sendrealsoon ) ;
 }
 return 0 ;
 }