VALUE asn1integer_to_num ( const ASN1_INTEGER * ai ) {
 BIGNUM * bn ;
 VALUE num ;
 if ( ! ai ) {
 ossl_raise ( rb_eTypeError , "ASN1_INTEGER is NULL!" ) ;
 }
 if ( ai -> type == V_ASN1_ENUMERATED ) bn = ASN1_ENUMERATED_to_BN ( ( ASN1_ENUMERATED * ) ai , NULL ) ;
 else bn = ASN1_INTEGER_to_BN ( ai , NULL ) ;
 if ( ! bn ) ossl_raise ( eOSSLError , NULL ) ;
 num = ossl_bn_new ( bn ) ;
 BN_free ( bn ) ;
 return num ;
 }