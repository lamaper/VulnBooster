static bool parse_nameConstraints ( chunk_t blob , int level0 , private_x509_cert_t * this ) {
 asn1_parser_t * parser ;
 identification_t * id ;
 chunk_t object ;
 int objectID ;
 bool success = FALSE ;
 parser = asn1_parser_create ( nameConstraintsObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 switch ( objectID ) {
 case NAME_CONSTRAINT_PERMITTED : id = parse_generalName ( object , parser -> get_level ( parser ) + 1 ) ;
 if ( ! id ) {
 goto end ;
 }
 this -> permitted_names -> insert_last ( this -> permitted_names , id ) ;
 break ;
 case NAME_CONSTRAINT_EXCLUDED : id = parse_generalName ( object , parser -> get_level ( parser ) + 1 ) ;
 if ( ! id ) {
 goto end ;
 }
 this -> excluded_names -> insert_last ( this -> excluded_names , id ) ;
 break ;
 default : break ;
 }
 }
 success = parser -> success ( parser ) ;
 end : parser -> destroy ( parser ) ;
 return success ;
 }