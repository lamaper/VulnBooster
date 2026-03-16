static VALUE ossl_asn1cons_each ( VALUE self ) {
 rb_ary_each ( ossl_asn1_get_value ( self ) ) ;
 return self ;
 }