static VALUE decode_bool ( unsigned char * der , long length ) {
 const unsigned char * p = der ;
 if ( length != 3 ) ossl_raise ( eASN1Error , "invalid length for BOOLEAN" ) ;
 if ( p [ 0 ] != 1 || p [ 1 ] != 1 ) ossl_raise ( eASN1Error , "invalid BOOLEAN" ) ;
 return p [ 2 ] ? Qtrue : Qfalse ;
 }