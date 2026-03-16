static bool compare_hostname ( const acl_host_and_ip * host , const char * hostname , const char * ip ) {
 long tmp ;
 if ( host -> ip_mask && ip && calc_ip ( ip , & tmp , '\0' ) ) {
 return ( tmp & host -> ip_mask ) == host -> ip ;
 }
 return ( ! host -> hostname || ( hostname && ! wild_case_compare ( system_charset_info , hostname , host -> hostname ) ) || ( ip && ! wild_compare ( ip , host -> hostname , 0 ) ) ) ;
 }