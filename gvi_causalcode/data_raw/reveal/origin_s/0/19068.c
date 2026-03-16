static u_int parse_constraint ( chunk_t object ) {
 switch ( object . len ) {
 case 0 : return 0 ;
 case 1 : return ( object . ptr [ 0 ] & 0x80 ) ? X509_NO_CONSTRAINT : object . ptr [ 0 ] ;
 default : return X509_NO_CONSTRAINT ;
 }
 }