bool x509_parse_crlDistributionPoints ( chunk_t blob , int level0 , linked_list_t * list ) {
 linked_list_t * uris , * issuers ;
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID ;
 bool success = FALSE ;
 uris = linked_list_create ( ) ;
 issuers = linked_list_create ( ) ;
 parser = asn1_parser_create ( crlDistributionPointsObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 switch ( objectID ) {
 case CRL_DIST_POINTS : add_cdps ( list , uris , issuers ) ;
 break ;
 case CRL_DIST_POINTS_FULLNAME : if ( ! x509_parse_generalNames ( object , parser -> get_level ( parser ) + 1 , TRUE , uris ) ) {
 goto end ;
 }
 break ;
 case CRL_DIST_POINTS_ISSUER : if ( ! x509_parse_generalNames ( object , parser -> get_level ( parser ) + 1 , TRUE , issuers ) ) {
 goto end ;
 }
 break ;
 default : break ;
 }
 }
 success = parser -> success ( parser ) ;
 add_cdps ( list , uris , issuers ) ;
 end : parser -> destroy ( parser ) ;
 uris -> destroy_offset ( uris , offsetof ( identification_t , destroy ) ) ;
 issuers -> destroy_offset ( issuers , offsetof ( identification_t , destroy ) ) ;
 return success ;
 }