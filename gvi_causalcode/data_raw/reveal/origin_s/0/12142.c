static void context_param ( void ) {
 gpg_error_t err ;
 int idx ;
 gcry_ctx_t ctx = NULL ;
 gcry_mpi_t q ;
 gcry_sexp_t keyparam ;
 wherestr = "context_param" ;
 show ( "checking standard curves\n" ) ;
 for ( idx = 0 ;
 test_curve [ idx ] . desc ;
 idx ++ ) {
 gcry_ctx_release ( ctx ) ;
 err = gcry_mpi_ec_new ( & ctx , NULL , test_curve [ idx ] . desc ) ;
 if ( err ) {
 fail ( "can't create context for curve '%s': %s\n" , test_curve [ idx ] . desc , gpg_strerror ( err ) ) ;
 continue ;
 }
 if ( get_and_cmp_mpi ( "p" , test_curve [ idx ] . p , test_curve [ idx ] . desc , ctx ) ) continue ;
 if ( get_and_cmp_mpi ( "a" , test_curve [ idx ] . a , test_curve [ idx ] . desc , ctx ) ) continue ;
 if ( get_and_cmp_mpi ( "b" , test_curve [ idx ] . b , test_curve [ idx ] . desc , ctx ) ) continue ;
 if ( get_and_cmp_mpi ( "g.x" , test_curve [ idx ] . g_x , test_curve [ idx ] . desc , ctx ) ) continue ;
 if ( get_and_cmp_mpi ( "g.y" , test_curve [ idx ] . g_y , test_curve [ idx ] . desc , ctx ) ) continue ;
 if ( get_and_cmp_mpi ( "n" , test_curve [ idx ] . n , test_curve [ idx ] . desc , ctx ) ) continue ;
 if ( get_and_cmp_point ( "g" , test_curve [ idx ] . g_x , test_curve [ idx ] . g_y , test_curve [ idx ] . desc , ctx ) ) continue ;
 }
 gcry_ctx_release ( ctx ) ;
 show ( "checking sample public key\n" ) ;
 q = hex2mpi ( sample_p256_q ) ;
 err = gcry_sexp_build ( & keyparam , NULL , "(public-key(ecdsa(curve %s)(q %m)))" , "NIST P-256" , q ) ;
 if ( err ) die ( "gcry_sexp_build failed: %s\n" , gpg_strerror ( err ) ) ;
 gcry_mpi_release ( q ) ;
 err = gcry_mpi_ec_new ( & ctx , keyparam , NULL ) ;
 if ( err ) fail ( "gcry_mpi_ec_new failed for sample public key: %s\n" , gpg_strerror ( err ) ) ;
 else {
 gcry_sexp_t sexp ;
 get_and_cmp_mpi ( "q" , sample_p256_q , "NIST P-256" , ctx ) ;
 get_and_cmp_point ( "q" , sample_p256_q_x , sample_p256_q_y , "NIST P-256" , ctx ) ;
 err = gcry_pubkey_get_sexp ( & sexp , 0 , ctx ) ;
 if ( err ) fail ( "gcry_pubkey_get_sexp(0) failed: %s\n" , gpg_strerror ( err ) ) ;
 else if ( debug ) print_sexp ( "Result of gcry_pubkey_get_sexp (0):\n" , sexp ) ;
 gcry_sexp_release ( sexp ) ;
 err = gcry_pubkey_get_sexp ( & sexp , GCRY_PK_GET_PUBKEY , ctx ) ;
 if ( err ) fail ( "gcry_pubkey_get_sexp(GET_PUBKEY) failed: %s\n" , gpg_strerror ( err ) ) ;
 else if ( debug ) print_sexp ( "Result of gcry_pubkey_get_sexp (GET_PUBKEY):\n" , sexp ) ;
 gcry_sexp_release ( sexp ) ;
 err = gcry_pubkey_get_sexp ( & sexp , GCRY_PK_GET_SECKEY , ctx ) ;
 if ( gpg_err_code ( err ) != GPG_ERR_NO_SECKEY ) fail ( "gcry_pubkey_get_sexp(GET_SECKEY) returned wrong error: %s\n" , gpg_strerror ( err ) ) ;
 gcry_sexp_release ( sexp ) ;
 gcry_ctx_release ( ctx ) ;
 }
 gcry_sexp_release ( keyparam ) ;
 }