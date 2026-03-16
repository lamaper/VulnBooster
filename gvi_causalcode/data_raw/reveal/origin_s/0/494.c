static VALUE ossl_x509name_to_s ( int argc , VALUE * argv , VALUE self ) {
 X509_NAME * name ;
 VALUE flag , str ;
 BIO * out ;
 unsigned long iflag ;
 rb_scan_args ( argc , argv , "01" , & flag ) ;
 if ( NIL_P ( flag ) ) return ossl_x509name_to_s_old ( self ) ;
 else iflag = NUM2ULONG ( flag ) ;
 if ( ! ( out = BIO_new ( BIO_s_mem ( ) ) ) ) ossl_raise ( eX509NameError , NULL ) ;
 GetX509Name ( self , name ) ;
 if ( ! X509_NAME_print_ex ( out , name , 0 , iflag ) ) {
 BIO_free ( out ) ;
 ossl_raise ( eX509NameError , NULL ) ;
 }
 str = ossl_membio2str ( out ) ;
 return str ;
 }