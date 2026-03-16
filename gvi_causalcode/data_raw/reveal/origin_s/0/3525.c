chunk_t build_generalName ( identification_t * id ) {
 int context ;
 switch ( id -> get_type ( id ) ) {
 case ID_RFC822_ADDR : context = ASN1_CONTEXT_S_1 ;
 break ;
 case ID_FQDN : context = ASN1_CONTEXT_S_2 ;
 break ;
 case ID_DER_ASN1_DN : context = ASN1_CONTEXT_C_4 ;
 break ;
 case ID_IPV4_ADDR : case ID_IPV6_ADDR : context = ASN1_CONTEXT_S_7 ;
 break ;
 default : DBG1 ( DBG_ASN , "encoding %N as generalName not supported" , id_type_names , id -> get_type ( id ) ) ;
 return chunk_empty ;
 }
 return asn1_wrap ( context , "c" , id -> get_encoding ( id ) ) ;
 }