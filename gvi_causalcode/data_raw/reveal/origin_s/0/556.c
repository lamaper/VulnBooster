static bool parse_basicConstraints ( chunk_t blob , int level0 , private_x509_cert_t * this ) {
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID ;
 bool isCA = FALSE ;
 bool success ;
 parser = asn1_parser_create ( basicConstraintsObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 switch ( objectID ) {
 case BASIC_CONSTRAINTS_CA : isCA = object . len && * object . ptr ;
 DBG2 ( DBG_ASN , " %s" , isCA ? "TRUE" : "FALSE" ) ;
 if ( isCA ) {
 this -> flags |= X509_CA ;
 }
 break ;
 case BASIC_CONSTRAINTS_PATH_LEN : if ( isCA ) {
 this -> pathLenConstraint = parse_constraint ( object ) ;
 }
 break ;
 default : break ;
 }
 }
 success = parser -> success ( parser ) ;
 parser -> destroy ( parser ) ;
 return success ;
 }