chunk_t x509_parse_authorityKeyIdentifier ( chunk_t blob , int level0 , chunk_t * authKeySerialNumber ) {
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID ;
 chunk_t authKeyIdentifier = chunk_empty ;
 * authKeySerialNumber = chunk_empty ;
 parser = asn1_parser_create ( authKeyIdentifierObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 switch ( objectID ) {
 case AUTH_KEY_ID_KEY_ID : authKeyIdentifier = chunk_clone ( object ) ;
 break ;
 case AUTH_KEY_ID_CERT_ISSUER : break ;
 case AUTH_KEY_ID_CERT_SERIAL : * authKeySerialNumber = object ;
 break ;
 default : break ;
 }
 }
 parser -> destroy ( parser ) ;
 return authKeyIdentifier ;
 }