static VALUE ossl_asn1data_initialize ( VALUE self , VALUE value , VALUE tag , VALUE tag_class ) {
 if ( ! SYMBOL_P ( tag_class ) ) ossl_raise ( eASN1Error , "invalid tag class" ) ;
 if ( tag_class == sym_UNIVERSAL && NUM2INT ( tag ) > 31 ) ossl_raise ( eASN1Error , "tag number for Universal too large" ) ;
 ossl_asn1_set_tag ( self , tag ) ;
 ossl_asn1_set_value ( self , value ) ;
 ossl_asn1_set_tag_class ( self , tag_class ) ;
 ossl_asn1_set_infinite_length ( self , Qfalse ) ;
 return self ;
 }