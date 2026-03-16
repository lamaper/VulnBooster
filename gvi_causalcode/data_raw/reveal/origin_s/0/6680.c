static bool parse_authorityInfoAccess ( chunk_t blob , int level0 , private_x509_cert_t * this ) {
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID ;
 int accessMethod = OID_UNKNOWN ;
 bool success = FALSE ;
 parser = asn1_parser_create ( authInfoAccessObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 switch ( objectID ) {
 case AUTH_INFO_ACCESS_METHOD : accessMethod = asn1_known_oid ( object ) ;
 break ;
 case AUTH_INFO_ACCESS_LOCATION : {
 switch ( accessMethod ) {
 case OID_OCSP : case OID_CA_ISSUERS : {
 identification_t * id ;
 char * uri ;
 id = parse_generalName ( object , parser -> get_level ( parser ) + 1 ) ;
 if ( id == NULL ) {
 goto end ;
 }
 DBG2 ( DBG_ASN , " '%Y'" , id ) ;
 if ( accessMethod == OID_OCSP && gn_to_string ( id , & uri ) ) {
 this -> ocsp_uris -> insert_last ( this -> ocsp_uris , uri ) ;
 }
 id -> destroy ( id ) ;
 }
 break ;
 default : break ;
 }
 break ;
 }
 default : break ;
 }
 }
 success = parser -> success ( parser ) ;
 end : parser -> destroy ( parser ) ;
 return success ;
 }