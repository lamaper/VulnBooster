static VALUE ossl_x509name_initialize ( int argc , VALUE * argv , VALUE self ) {
 X509_NAME * name ;
 VALUE arg , template ;
 GetX509Name ( self , name ) ;
 if ( rb_scan_args ( argc , argv , "02" , & arg , & template ) == 0 ) {
 return self ;
 }
 else {
 VALUE tmp = rb_check_array_type ( arg ) ;
 if ( ! NIL_P ( tmp ) ) {
 VALUE args ;
 if ( NIL_P ( template ) ) template = OBJECT_TYPE_TEMPLATE ;
 args = rb_ary_new3 ( 2 , self , template ) ;
 rb_block_call ( tmp , rb_intern ( "each" ) , 0 , 0 , ossl_x509name_init_i , args ) ;
 }
 else {
 const unsigned char * p ;
 VALUE str = ossl_to_der_if_possible ( arg ) ;
 X509_NAME * x ;
 StringValue ( str ) ;
 p = ( unsigned char * ) RSTRING_PTR ( str ) ;
 x = d2i_X509_NAME ( & name , & p , RSTRING_LEN ( str ) ) ;
 DATA_PTR ( self ) = name ;
 if ( ! x ) {
 ossl_raise ( eX509NameError , NULL ) ;
 }
 }
 }
 return self ;
 }