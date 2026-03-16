static ASN1_BOOLEAN obj_to_asn1bool ( VALUE obj ) {
 if ( NIL_P ( obj ) ) ossl_raise ( rb_eTypeError , "Can't convert nil into Boolean" ) ;
 return RTEST ( obj ) ? 0xff : 0x0 ;
 }