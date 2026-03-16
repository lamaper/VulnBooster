static VALUE ossl_asn1obj_get_oid ( VALUE self ) {
 VALUE val ;
 ASN1_OBJECT * a1obj ;
 char buf [ 128 ] ;
 val = ossl_asn1_get_value ( self ) ;
 a1obj = obj_to_asn1obj ( val ) ;
 OBJ_obj2txt ( buf , sizeof ( buf ) , a1obj , 1 ) ;
 ASN1_OBJECT_free ( a1obj ) ;
 return rb_str_new2 ( buf ) ;
 }