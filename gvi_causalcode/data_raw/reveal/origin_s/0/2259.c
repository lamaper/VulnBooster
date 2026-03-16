static gpg_error_t ec_p_new ( gcry_ctx_t * r_ctx , gcry_mpi_t p , gcry_mpi_t a ) {
 gpg_error_t err ;
 gcry_sexp_t sexp ;
 if ( p && a ) err = gcry_sexp_build ( & sexp , NULL , "(ecdsa (p %m)(a %m))" , p , a ) ;
 else if ( p ) err = gcry_sexp_build ( & sexp , NULL , "(ecdsa (p %m))" , p ) ;
 else if ( a ) err = gcry_sexp_build ( & sexp , NULL , "(ecdsa (a %m))" , a ) ;
 else err = gcry_sexp_build ( & sexp , NULL , "(ecdsa)" ) ;
 if ( err ) return err ;
 err = gcry_mpi_ec_new ( r_ctx , sexp , NULL ) ;
 gcry_sexp_release ( sexp ) ;
 return err ;
 }