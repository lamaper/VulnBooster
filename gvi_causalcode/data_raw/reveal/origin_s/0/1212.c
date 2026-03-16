unsigned int srtp_get_version ( ) {
 unsigned int major = 0 , minor = 0 , micro = 0 ;
 unsigned int rv = 0 ;
 int parse_rv ;
 parse_rv = sscanf ( SRTP_VERSION , "%u.%u.%u" , & major , & minor , & micro ) ;
 if ( parse_rv != 3 ) {
 return ( 0 ) ;
 }
 rv |= ( major & 0xFF ) << 24 ;
 rv |= ( minor & 0xFF ) << 16 ;
 rv |= micro & 0xFF ;
 return rv ;
 }