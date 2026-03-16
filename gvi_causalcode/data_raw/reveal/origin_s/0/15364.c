chunk_t x509_build_subjectAltNames ( linked_list_t * list ) {
 chunk_t subjectAltNames = chunk_empty , name ;
 enumerator_t * enumerator ;
 identification_t * id ;
 if ( list -> get_count ( list ) == 0 ) {
 return chunk_empty ;
 }
 enumerator = list -> create_enumerator ( list ) ;
 while ( enumerator -> enumerate ( enumerator , & id ) ) {
 name = build_generalName ( id ) ;
 subjectAltNames = chunk_cat ( "mm" , subjectAltNames , name ) ;
 }
 enumerator -> destroy ( enumerator ) ;
 return asn1_wrap ( ASN1_SEQUENCE , "mm" , asn1_build_known_oid ( OID_SUBJECT_ALT_NAME ) , asn1_wrap ( ASN1_OCTET_STRING , "m" , asn1_wrap ( ASN1_SEQUENCE , "m" , subjectAltNames ) ) ) ;
 }