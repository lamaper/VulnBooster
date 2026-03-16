static ASN1_OBJECT * obj_to_asn1obj ( VALUE obj ) {
 ASN1_OBJECT * a1obj ;
 StringValueCStr ( obj ) ;
 a1obj = OBJ_txt2obj ( RSTRING_PTR ( obj ) , 0 ) ;
 if ( ! a1obj ) a1obj = OBJ_txt2obj ( RSTRING_PTR ( obj ) , 1 ) ;
 if ( ! a1obj ) ossl_raise ( eASN1Error , "invalid OBJECT ID %" PRIsVALUE , obj ) ;
 return a1obj ;
 }