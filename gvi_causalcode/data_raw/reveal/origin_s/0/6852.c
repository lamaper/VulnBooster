static bool parse_ipAddrBlocks ( chunk_t blob , int level0 , private_x509_cert_t * this ) {
 asn1_parser_t * parser ;
 chunk_t object , min_object ;
 ts_type_t ts_type = 0 ;
 traffic_selector_t * ts ;
 int objectID ;
 bool success = FALSE ;
 parser = asn1_parser_create ( ipAddrBlocksObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 switch ( objectID ) {
 case IP_ADDR_BLOCKS_FAMILY : ts_type = 0 ;
 if ( object . len == 2 && object . ptr [ 0 ] == 0 ) {
 if ( object . ptr [ 1 ] == 1 ) {
 ts_type = TS_IPV4_ADDR_RANGE ;
 }
 else if ( object . ptr [ 1 ] == 2 ) {
 ts_type = TS_IPV6_ADDR_RANGE ;
 }
 else {
 break ;
 }
 DBG2 ( DBG_ASN , " %N" , ts_type_name , ts_type ) ;
 }
 break ;
 case IP_ADDR_BLOCKS_INHERIT : DBG1 ( DBG_ASN , "inherit choice is not supported" ) ;
 break ;
 case IP_ADDR_BLOCKS_PREFIX : if ( ! check_address_object ( ts_type , object ) ) {
 goto end ;
 }
 ts = traffic_selector_create_from_rfc3779_format ( ts_type , object , object ) ;
 DBG2 ( DBG_ASN , " %R" , ts ) ;
 this -> ipAddrBlocks -> insert_last ( this -> ipAddrBlocks , ts ) ;
 break ;
 case IP_ADDR_BLOCKS_MIN : if ( ! check_address_object ( ts_type , object ) ) {
 goto end ;
 }
 min_object = object ;
 break ;
 case IP_ADDR_BLOCKS_MAX : if ( ! check_address_object ( ts_type , object ) ) {
 goto end ;
 }
 ts = traffic_selector_create_from_rfc3779_format ( ts_type , min_object , object ) ;
 DBG2 ( DBG_ASN , " %R" , ts ) ;
 this -> ipAddrBlocks -> insert_last ( this -> ipAddrBlocks , ts ) ;
 break ;
 default : break ;
 }
 }
 success = parser -> success ( parser ) ;
 this -> flags |= X509_IP_ADDR_BLOCKS ;
 end : parser -> destroy ( parser ) ;
 return success ;
 }