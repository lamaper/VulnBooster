bool x509_parse_generalNames ( chunk_t blob , int level0 , bool implicit , linked_list_t * list ) {
 asn1_parser_t * parser ;
 chunk_t object ;
 identification_t * gn ;
 int objectID ;
 bool success = FALSE ;
 parser = asn1_parser_create ( generalNamesObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 parser -> set_flags ( parser , implicit , FALSE ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 if ( objectID == GENERAL_NAMES_GN ) {
 gn = parse_generalName ( object , parser -> get_level ( parser ) + 1 ) ;
 if ( ! gn ) {
 goto end ;
 }
 list -> insert_last ( list , ( void * ) gn ) ;
 }
 }
 success = parser -> success ( parser ) ;
 end : parser -> destroy ( parser ) ;
 return success ;
 }