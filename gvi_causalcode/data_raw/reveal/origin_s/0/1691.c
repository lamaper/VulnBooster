static int check_authenticated_user_and_ip ( int userid , struct query * q ) {
 int res = check_user_and_ip ( userid , q ) ;
 if ( res ) return res ;
 if ( ! users [ userid ] . authenticated ) return 1 ;
 return 0 ;
 }