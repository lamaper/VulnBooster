gcry_error_t gcry_sexp_sscan ( gcry_sexp_t * retsexp , size_t * erroff , const char * buffer , size_t length ) {
 return sexp_sscan ( retsexp , erroff , buffer , length , 0 , NULL ) ;
 }