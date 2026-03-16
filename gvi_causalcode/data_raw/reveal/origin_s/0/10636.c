static ASN1_NULL * obj_to_asn1null ( VALUE obj ) {
 ASN1_NULL * null ;
 if ( ! NIL_P ( obj ) ) ossl_raise ( eASN1Error , "nil expected" ) ;
 if ( ! ( null = ASN1_NULL_new ( ) ) ) ossl_raise ( eASN1Error , NULL ) ;
 return null ;
 }