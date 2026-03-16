static gpg_err_code_t point_from_keyparam ( gcry_mpi_point_t * r_a , gcry_sexp_t keyparam , const char * name ) {
 gcry_err_code_t ec ;
 gcry_mpi_t a = NULL ;
 gcry_mpi_point_t point ;
 ec = mpi_from_keyparam ( & a , keyparam , name ) ;
 if ( ec ) return ec ;
 if ( a ) {
 point = gcry_mpi_point_new ( 0 ) ;
 ec = _gcry_ecc_os2ec ( point , a ) ;
 mpi_free ( a ) ;
 if ( ec ) {
 gcry_mpi_point_release ( point ) ;
 return ec ;
 }
 }
 else {
 char * tmpname ;
 gcry_mpi_t x = NULL ;
 gcry_mpi_t y = NULL ;
 gcry_mpi_t z = NULL ;
 tmpname = gcry_malloc ( strlen ( name ) + 2 + 1 ) ;
 if ( ! tmpname ) return gpg_err_code_from_syserror ( ) ;
 strcpy ( stpcpy ( tmpname , name ) , ".x" ) ;
 ec = mpi_from_keyparam ( & x , keyparam , tmpname ) ;
 if ( ec ) {
 gcry_free ( tmpname ) ;
 return ec ;
 }
 strcpy ( stpcpy ( tmpname , name ) , ".y" ) ;
 ec = mpi_from_keyparam ( & y , keyparam , tmpname ) ;
 if ( ec ) {
 mpi_free ( x ) ;
 gcry_free ( tmpname ) ;
 return ec ;
 }
 strcpy ( stpcpy ( tmpname , name ) , ".z" ) ;
 ec = mpi_from_keyparam ( & z , keyparam , tmpname ) ;
 if ( ec ) {
 mpi_free ( y ) ;
 mpi_free ( x ) ;
 gcry_free ( tmpname ) ;
 return ec ;
 }
 if ( ! z ) z = mpi_set_ui ( NULL , 1 ) ;
 if ( x && y ) point = gcry_mpi_point_snatch_set ( NULL , x , y , z ) ;
 else {
 mpi_free ( x ) ;
 mpi_free ( y ) ;
 mpi_free ( z ) ;
 point = NULL ;
 }
 gcry_free ( tmpname ) ;
 }
 if ( point ) * r_a = point ;
 return 0 ;
 }