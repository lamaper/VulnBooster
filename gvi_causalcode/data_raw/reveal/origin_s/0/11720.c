const char * SSL_rstate_string_long ( const SSL * s ) {
 const char * str ;
 switch ( s -> rstate ) {
 case SSL_ST_READ_HEADER : str = "read header" ;
 break ;
 case SSL_ST_READ_BODY : str = "read body" ;
 break ;
 case SSL_ST_READ_DONE : str = "read done" ;
 break ;
 default : str = "unknown" ;
 break ;
 }
 return ( str ) ;
 }