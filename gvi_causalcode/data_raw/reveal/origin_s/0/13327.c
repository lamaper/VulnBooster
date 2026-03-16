static bool check_address_object ( ts_type_t ts_type , chunk_t object ) {
 switch ( ts_type ) {
 case TS_IPV4_ADDR_RANGE : if ( object . len > 5 ) {
 DBG1 ( DBG_ASN , "IPv4 address object is larger than 5 octets" ) ;
 return FALSE ;
 }
 break ;
 case TS_IPV6_ADDR_RANGE : if ( object . len > 17 ) {
 DBG1 ( DBG_ASN , "IPv6 address object is larger than 17 octets" ) ;
 return FALSE ;
 }
 break ;
 default : DBG1 ( DBG_ASN , "unknown address family" ) ;
 return FALSE ;
 }
 if ( object . len == 0 ) {
 DBG1 ( DBG_ASN , "An ASN.1 bit string must contain at least the " "initial octet" ) ;
 return FALSE ;
 }
 if ( object . len == 1 && object . ptr [ 0 ] != 0 ) {
 DBG1 ( DBG_ASN , "An empty ASN.1 bit string must contain a zero " "initial octet" ) ;
 return FALSE ;
 }
 if ( object . ptr [ 0 ] > 7 ) {
 DBG1 ( DBG_ASN , "number of unused bits is too large" ) ;
 return FALSE ;
 }
 return TRUE ;
 }