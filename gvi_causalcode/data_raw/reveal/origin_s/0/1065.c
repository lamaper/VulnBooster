const char * SSL_alert_type_string_long ( int value ) {
 value >>= 8 ;
 if ( value == SSL3_AL_WARNING ) return ( "warning" ) ;
 else if ( value == SSL3_AL_FATAL ) return ( "fatal" ) ;
 else return ( "unknown" ) ;
 }