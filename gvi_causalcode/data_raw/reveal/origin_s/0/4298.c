gcry_error_t gcry_sexp_build_array ( gcry_sexp_t * retsexp , size_t * erroff , const char * format , void * * arg_list ) {
 return sexp_sscan ( retsexp , erroff , format , strlen ( format ) , 1 , arg_list ) ;
 }