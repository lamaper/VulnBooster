ASN1_INTEGER * num_to_asn1integer ( VALUE obj , ASN1_INTEGER * ai ) {
 BIGNUM * bn ;
 if ( NIL_P ( obj ) ) ossl_raise ( rb_eTypeError , "Can't convert nil into Integer" ) ;
 bn = GetBNPtr ( obj ) ;
 if ( ! ( ai = BN_to_ASN1_INTEGER ( bn , ai ) ) ) ossl_raise ( eOSSLError , NULL ) ;
 return ai ;
 }