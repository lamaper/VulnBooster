static bool parse_policyConstraints ( chunk_t blob , int level0 , private_x509_cert_t * this ) {
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID ;
 bool success ;
 parser = asn1_parser_create ( policyConstraintsObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 switch ( objectID ) {
 case POLICY_CONSTRAINT_EXPLICIT : this -> require_explicit = parse_constraint ( object ) ;
 break ;
 case POLICY_CONSTRAINT_INHIBIT : this -> inhibit_mapping = parse_constraint ( object ) ;
 break ;
 default : break ;
 }
 }
 success = parser -> success ( parser ) ;
 parser -> destroy ( parser ) ;
 return success ;
 }