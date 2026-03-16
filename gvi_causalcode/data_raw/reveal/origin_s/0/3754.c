gcry_error_t gcry_sexp_new ( gcry_sexp_t * retsexp , const void * buffer , size_t length , int autodetect ) {
 return gcry_sexp_create ( retsexp , ( void * ) buffer , length , autodetect , NULL ) ;
 }