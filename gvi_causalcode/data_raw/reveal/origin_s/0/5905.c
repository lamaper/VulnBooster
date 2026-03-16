static VALUE ossl_asn1obj_s_register ( VALUE self , VALUE oid , VALUE sn , VALUE ln ) {
 StringValueCStr ( oid ) ;
 StringValueCStr ( sn ) ;
 StringValueCStr ( ln ) ;
 if ( ! OBJ_create ( RSTRING_PTR ( oid ) , RSTRING_PTR ( sn ) , RSTRING_PTR ( ln ) ) ) ossl_raise ( eASN1Error , NULL ) ;
 return Qtrue ;
 }