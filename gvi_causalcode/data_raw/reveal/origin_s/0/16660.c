static VALUE ossl_x509name_to_a ( VALUE self ) {
 X509_NAME * name ;
 X509_NAME_ENTRY * entry ;
 int i , entries , nid ;
 char long_name [ 512 ] ;
 const char * short_name ;
 VALUE ary , vname , ret ;
 ASN1_STRING * value ;
 GetX509Name ( self , name ) ;
 entries = X509_NAME_entry_count ( name ) ;
 if ( entries < 0 ) {
 OSSL_Debug ( "name entries < 0!" ) ;
 return rb_ary_new ( ) ;
 }
 ret = rb_ary_new2 ( entries ) ;
 for ( i = 0 ;
 i < entries ;
 i ++ ) {
 if ( ! ( entry = X509_NAME_get_entry ( name , i ) ) ) {
 ossl_raise ( eX509NameError , NULL ) ;
 }
 if ( ! i2t_ASN1_OBJECT ( long_name , sizeof ( long_name ) , X509_NAME_ENTRY_get_object ( entry ) ) ) {
 ossl_raise ( eX509NameError , NULL ) ;
 }
 nid = OBJ_ln2nid ( long_name ) ;
 if ( nid == NID_undef ) {
 vname = rb_str_new2 ( ( const char * ) & long_name ) ;
 }
 else {
 short_name = OBJ_nid2sn ( nid ) ;
 vname = rb_str_new2 ( short_name ) ;
 }
 value = X509_NAME_ENTRY_get_data ( entry ) ;
 ary = rb_ary_new3 ( 3 , vname , asn1str_to_str ( value ) , INT2NUM ( value -> type ) ) ;
 rb_ary_push ( ret , ary ) ;
 }
 return ret ;
 }