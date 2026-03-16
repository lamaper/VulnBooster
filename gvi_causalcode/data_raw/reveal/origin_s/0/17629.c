static identification_t * parse_generalName ( chunk_t blob , int level0 ) {
 asn1_parser_t * parser ;
 chunk_t object ;
 int objectID ;
 identification_t * gn = NULL ;
 parser = asn1_parser_create ( generalNameObjects , blob ) ;
 parser -> set_top_level ( parser , level0 ) ;
 while ( parser -> iterate ( parser , & objectID , & object ) ) {
 id_type_t id_type = ID_ANY ;
 switch ( objectID ) {
 case GN_OBJ_RFC822_NAME : id_type = ID_RFC822_ADDR ;
 break ;
 case GN_OBJ_DNS_NAME : id_type = ID_FQDN ;
 break ;
 case GN_OBJ_URI : id_type = ID_DER_ASN1_GN_URI ;
 break ;
 case GN_OBJ_DIRECTORY_NAME : id_type = ID_DER_ASN1_DN ;
 break ;
 case GN_OBJ_IP_ADDRESS : switch ( object . len ) {
 case 4 : id_type = ID_IPV4_ADDR ;
 break ;
 case 16 : id_type = ID_IPV6_ADDR ;
 break ;
 default : break ;
 }
 break ;
 case GN_OBJ_OTHER_NAME : if ( ! parse_otherName ( & object , parser -> get_level ( parser ) + 1 , & id_type ) ) {
 goto end ;
 }
 break ;
 case GN_OBJ_X400_ADDRESS : case GN_OBJ_EDI_PARTY_NAME : case GN_OBJ_REGISTERED_ID : default : break ;
 }
 if ( id_type != ID_ANY ) {
 gn = identification_create_from_encoding ( id_type , object ) ;
 DBG2 ( DBG_ASN , " '%Y'" , gn ) ;
 goto end ;
 }
 }
 end : parser -> destroy ( parser ) ;
 return gn ;
 }