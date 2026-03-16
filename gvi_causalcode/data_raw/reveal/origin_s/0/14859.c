static ASN1_BIT_STRING * obj_to_asn1bstr ( VALUE obj , long unused_bits ) {
 ASN1_BIT_STRING * bstr ;
 if ( unused_bits < 0 ) unused_bits = 0 ;
 StringValue ( obj ) ;
 if ( ! ( bstr = ASN1_BIT_STRING_new ( ) ) ) ossl_raise ( eASN1Error , NULL ) ;
 ASN1_BIT_STRING_set ( bstr , ( unsigned char * ) RSTRING_PTR ( obj ) , RSTRING_LENINT ( obj ) ) ;
 bstr -> flags &= ~ ( ASN1_STRING_FLAG_BITS_LEFT | 0x07 ) ;
 bstr -> flags |= ASN1_STRING_FLAG_BITS_LEFT | ( unused_bits & 0x07 ) ;
 return bstr ;
 }