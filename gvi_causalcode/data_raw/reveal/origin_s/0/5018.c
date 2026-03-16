static gpg_err_code_t mpi_from_keyparam ( gcry_mpi_t * r_a , gcry_sexp_t keyparam , const char * name ) {
 gcry_err_code_t ec = 0 ;
 gcry_sexp_t l1 ;
 l1 = gcry_sexp_find_token ( keyparam , name , 0 ) ;
 if ( l1 ) {
 * r_a = gcry_sexp_nth_mpi ( l1 , 1 , GCRYMPI_FMT_USG ) ;
 gcry_sexp_release ( l1 ) ;
 if ( ! * r_a ) ec = GPG_ERR_INV_OBJ ;
 }
 return ec ;
 }