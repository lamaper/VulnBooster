static int ossl_asn1_default_tag ( VALUE obj ) {
 VALUE tmp_class , tag ;
 tmp_class = CLASS_OF ( obj ) ;
 while ( ! NIL_P ( tmp_class ) ) {
 tag = rb_hash_lookup ( class_tag_map , tmp_class ) ;
 if ( tag != Qnil ) return NUM2INT ( tag ) ;
 tmp_class = rb_class_superclass ( tmp_class ) ;
 }
 ossl_raise ( eASN1Error , "universal tag for %" PRIsVALUE " not found" , rb_obj_class ( obj ) ) ;
 }