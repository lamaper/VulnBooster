static VALUE ossl_x509name_add_entry ( int argc , VALUE * argv , VALUE self ) {
 X509_NAME * name ;
 VALUE oid , value , type ;
 const char * oid_name ;
 rb_scan_args ( argc , argv , "21" , & oid , & value , & type ) ;
 oid_name = StringValueCStr ( oid ) ;
 StringValue ( value ) ;
 if ( NIL_P ( type ) ) type = rb_aref ( OBJECT_TYPE_TEMPLATE , oid ) ;
 GetX509Name ( self , name ) ;
 if ( ! X509_NAME_add_entry_by_txt ( name , oid_name , NUM2INT ( type ) , ( const unsigned char * ) RSTRING_PTR ( value ) , RSTRING_LENINT ( value ) , - 1 , 0 ) ) {
 ossl_raise ( eX509NameError , NULL ) ;
 }
 return self ;
 }