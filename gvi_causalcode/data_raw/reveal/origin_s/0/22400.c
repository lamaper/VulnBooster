static VALUE ossl_asn1_initialize ( int argc , VALUE * argv , VALUE self ) {
 VALUE value , tag , tagging , tag_class ;
 rb_scan_args ( argc , argv , "13" , & value , & tag , & tagging , & tag_class ) ;
 if ( argc > 1 ) {
 if ( NIL_P ( tag ) ) ossl_raise ( eASN1Error , "must specify tag number" ) ;
 if ( ! NIL_P ( tagging ) && ! SYMBOL_P ( tagging ) ) ossl_raise ( eASN1Error , "invalid tagging method" ) ;
 if ( NIL_P ( tag_class ) ) {
 if ( NIL_P ( tagging ) ) tag_class = sym_UNIVERSAL ;
 else tag_class = sym_CONTEXT_SPECIFIC ;
 }
 if ( ! SYMBOL_P ( tag_class ) ) ossl_raise ( eASN1Error , "invalid tag class" ) ;
 if ( tagging == sym_IMPLICIT && NUM2INT ( tag ) > 31 ) ossl_raise ( eASN1Error , "tag number for Universal too large" ) ;
 }
 else {
 tag = INT2NUM ( ossl_asn1_default_tag ( self ) ) ;
 tagging = Qnil ;
 tag_class = sym_UNIVERSAL ;
 }
 ossl_asn1_set_tag ( self , tag ) ;
 ossl_asn1_set_value ( self , value ) ;
 ossl_asn1_set_tagging ( self , tagging ) ;
 ossl_asn1_set_tag_class ( self , tag_class ) ;
 ossl_asn1_set_infinite_length ( self , Qfalse ) ;
 return self ;
 }