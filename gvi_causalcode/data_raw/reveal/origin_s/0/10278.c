static gcry_error_t sexp_sscan ( gcry_sexp_t * retsexp , size_t * erroff , const char * buffer , size_t length , int argflag , void * * arg_list , ... ) {
 gcry_error_t rc ;
 va_list arg_ptr ;
 va_start ( arg_ptr , arg_list ) ;
 rc = vsexp_sscan ( retsexp , erroff , buffer , length , argflag , arg_list , arg_ptr ) ;
 va_end ( arg_ptr ) ;
 return rc ;
 }