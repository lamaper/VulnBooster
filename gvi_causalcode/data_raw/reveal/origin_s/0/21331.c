const char * SSL_alert_type_string ( int value ) {
 value >>= 8 ;
 if ( value == SSL3_AL_WARNING ) return ( "W" ) ;
 else if ( value == SSL3_AL_FATAL ) return ( "F" ) ;
 else return ( "U" ) ;
 }