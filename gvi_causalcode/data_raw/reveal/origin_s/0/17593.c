gcry_error_t _gcry_sexp_vbuild ( gcry_sexp_t * retsexp , size_t * erroff , const char * format , va_list arg_ptr ) {
 return vsexp_sscan ( retsexp , erroff , format , strlen ( format ) , 1 , NULL , arg_ptr ) ;
 }