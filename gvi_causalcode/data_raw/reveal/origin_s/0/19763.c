static bool parse_otherName ( chunk_t * blob , int level0 , id_type_t * type ) {
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID ;
 int oid = OID_UNKNOWN ;
 bool success = FALSE ;
 parser = asn1_parser_create ( otherNameObjects , * blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 switch ( objectID ) {
 case ON_OBJ_ID_TYPE : oid = asn1_known_oid ( object ) ;
 break ;
 case ON_OBJ_VALUE : switch ( oid ) {
 case OID_XMPP_ADDR : if ( ! asn1_parse_simple_object ( & object , ASN1_UTF8STRING , parser -> get_level ( parser ) + 1 , "xmppAddr" ) ) {
 goto end ;
 }
 break ;
 case OID_USER_PRINCIPAL_NAME : if ( asn1_parse_simple_object ( & object , ASN1_UTF8STRING , parser -> get_level ( parser ) + 1 , "msUPN" ) ) {
 * blob = object ;
 * type = ID_RFC822_ADDR ;
 }
 else {
 goto end ;
 }
 break ;
 }
 break ;
 default : break ;
 }
 }
 success = parser -> success ( parser ) ;
 end : parser -> destroy ( parser ) ;
 return success ;
 }