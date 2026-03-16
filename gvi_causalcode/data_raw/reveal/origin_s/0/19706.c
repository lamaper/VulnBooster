static VALUE ossl_asn1obj_get_sn ( VALUE self ) {
 VALUE val , ret = Qnil ;
 int nid ;
 val = ossl_asn1_get_value ( self ) ;
 if ( ( nid = OBJ_txt2nid ( StringValueCStr ( val ) ) ) != NID_undef ) ret = rb_str_new2 ( OBJ_nid2sn ( nid ) ) ;
 return ret ;
 }