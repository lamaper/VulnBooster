static VALUE ossl_asn1eoc_initialize ( VALUE self ) {
 VALUE tag , tagging , tag_class , value ;
 tag = INT2NUM ( ossl_asn1_default_tag ( self ) ) ;
 tagging = Qnil ;
 tag_class = sym_UNIVERSAL ;
 value = rb_str_new ( "" , 0 ) ;
 ossl_asn1_set_tag ( self , tag ) ;
 ossl_asn1_set_value ( self , value ) ;
 ossl_asn1_set_tagging ( self , tagging ) ;
 ossl_asn1_set_tag_class ( self , tag_class ) ;
 ossl_asn1_set_infinite_length ( self , Qfalse ) ;
 return self ;
 }