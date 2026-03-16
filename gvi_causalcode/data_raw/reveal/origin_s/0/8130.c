static ASN1_STRING * obj_to_asn1str ( VALUE obj ) {
 ASN1_STRING * str ;
 StringValue ( obj ) ;
 if ( ! ( str = ASN1_STRING_new ( ) ) ) ossl_raise ( eASN1Error , NULL ) ;
 ASN1_STRING_set ( str , RSTRING_PTR ( obj ) , RSTRING_LENINT ( obj ) ) ;
 return str ;
 }