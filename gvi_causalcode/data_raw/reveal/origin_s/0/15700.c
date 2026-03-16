static VALUE decode_eoc ( unsigned char * der , long length ) {
 if ( length != 2 || ! ( der [ 0 ] == 0x00 && der [ 1 ] == 0x00 ) ) ossl_raise ( eASN1Error , NULL ) ;
 return rb_str_new ( "" , 0 ) ;
 }