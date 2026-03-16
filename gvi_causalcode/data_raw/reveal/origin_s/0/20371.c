static void update_hostname ( acl_host_and_ip * host , const char * hostname ) {
 host -> hostname = ( char * ) hostname ;
 if ( ! hostname || ( ! ( hostname = calc_ip ( hostname , & host -> ip , '/' ) ) || ! ( hostname = calc_ip ( hostname + 1 , & host -> ip_mask , '\0' ) ) ) ) {
 host -> ip = host -> ip_mask = 0 ;
 }
 }