gcry_error_t gcry_sexp_build ( gcry_sexp_t * retsexp , size_t * erroff , const char * format , ... ) {
 gcry_error_t rc ;
 va_list arg_ptr ;
 va_start ( arg_ptr , format ) ;
 rc = vsexp_sscan ( retsexp , erroff , format , strlen ( format ) , 1 , NULL , arg_ptr ) ;
 va_end ( arg_ptr ) ;
 return rc ;
 }