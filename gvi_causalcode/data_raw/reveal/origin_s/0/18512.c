static ASN1_STRING * obj_to_asn1derstr ( VALUE obj ) {
 ASN1_STRING * a1str ;
 VALUE str ;
 str = ossl_to_der ( obj ) ;
 if ( ! ( a1str = ASN1_STRING_new ( ) ) ) ossl_raise ( eASN1Error , NULL ) ;
 ASN1_STRING_set ( a1str , RSTRING_PTR ( str ) , RSTRING_LENINT ( str ) ) ;
 return a1str ;
 }