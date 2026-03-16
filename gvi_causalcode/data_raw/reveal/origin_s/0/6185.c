static bool parse_policyMappings ( chunk_t blob , int level0 , private_x509_cert_t * this ) {
 x509_policy_mapping_t * map = NULL ;
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID ;
 bool success ;
 parser = asn1_parser_create ( policyMappingsObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 switch ( objectID ) {
 case POLICY_MAPPING : INIT ( map ) ;
 this -> policy_mappings -> insert_last ( this -> policy_mappings , map ) ;
 break ;
 case POLICY_MAPPING_ISSUER : if ( map && ! map -> issuer . len ) {
 map -> issuer = chunk_clone ( object ) ;
 }
 break ;
 case POLICY_MAPPING_SUBJECT : if ( map && ! map -> subject . len ) {
 map -> subject = chunk_clone ( object ) ;
 }
 break ;
 default : break ;
 }
 }
 success = parser -> success ( parser ) ;
 parser -> destroy ( parser ) ;
 return success ;
 }