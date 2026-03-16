static void context_alloc ( void ) {
 gpg_error_t err ;
 gcry_ctx_t ctx ;
 gcry_mpi_t p , a ;
 wherestr = "context_alloc" ;
 show ( "checking context functions\n" ) ;
 p = gcry_mpi_set_ui ( NULL , 1 ) ;
 a = gcry_mpi_set_ui ( NULL , 1 ) ;
 err = ec_p_new ( & ctx , p , a ) ;
 if ( err ) die ( "ec_p_new returned an error: %s\n" , gpg_strerror ( err ) ) ;
 gcry_mpi_release ( p ) ;
 gcry_mpi_release ( a ) ;
 gcry_ctx_release ( ctx ) ;
 p = gcry_mpi_set_ui ( NULL , 0 ) ;
 a = gcry_mpi_set_ui ( NULL , 0 ) ;
 err = ec_p_new ( & ctx , p , a ) ;
 if ( ! err || gpg_err_code ( err ) != GPG_ERR_EINVAL ) fail ( "ec_p_new: bad parameter detection failed (1)\n" ) ;
 gcry_mpi_set_ui ( p , 1 ) ;
 err = ec_p_new ( & ctx , p , a ) ;
 if ( ! err || gpg_err_code ( err ) != GPG_ERR_EINVAL ) fail ( "ec_p_new: bad parameter detection failed (2)\n" ) ;
 gcry_mpi_release ( p ) ;
 p = NULL ;
 err = ec_p_new ( & ctx , p , a ) ;
 if ( ! err || gpg_err_code ( err ) != GPG_ERR_EINVAL ) fail ( "ec_p_new: bad parameter detection failed (3)\n" ) ;
 gcry_mpi_release ( a ) ;
 a = NULL ;
 err = ec_p_new ( & ctx , p , a ) ;
 if ( ! err || gpg_err_code ( err ) != GPG_ERR_EINVAL ) fail ( "ec_p_new: bad parameter detection failed (4)\n" ) ;
 }