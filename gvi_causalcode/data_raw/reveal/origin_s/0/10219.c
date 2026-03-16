const char * SSL_rstate_string ( const SSL * s ) {
 const char * str ;
 switch ( s -> rstate ) {
 case SSL_ST_READ_HEADER : str = "RH" ;
 break ;
 case SSL_ST_READ_BODY : str = "RB" ;
 break ;
 case SSL_ST_READ_DONE : str = "RD" ;
 break ;
 default : str = "unknown" ;
 break ;
 }
 return ( str ) ;
 }