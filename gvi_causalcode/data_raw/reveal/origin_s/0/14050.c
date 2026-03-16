static int ossl_asn1_tag ( VALUE obj ) {
 VALUE tag ;
 tag = ossl_asn1_get_tag ( obj ) ;
 if ( NIL_P ( tag ) ) ossl_raise ( eASN1Error , "tag number not specified" ) ;
 return NUM2INT ( tag ) ;
 }