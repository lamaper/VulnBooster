static int check_user_and_ip ( int userid , struct query * q ) {
 struct sockaddr_in * tempin ;
 if ( userid < 0 || userid >= created_users ) {
 return 1 ;
 }
 if ( ! users [ userid ] . active || users [ userid ] . disabled ) {
 return 1 ;
 }
 if ( users [ userid ] . last_pkt + 60 < time ( NULL ) ) {
 return 1 ;
 }
 if ( ! check_ip ) {
 return 0 ;
 }
 tempin = ( struct sockaddr_in * ) & ( q -> from ) ;
 return memcmp ( & ( users [ userid ] . host ) , & ( tempin -> sin_addr ) , sizeof ( struct in_addr ) ) ;
 }