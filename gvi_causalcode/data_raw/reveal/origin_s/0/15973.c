gcry_error_t gcry_mpi_aprint ( enum gcry_mpi_format format , unsigned char * * buffer , size_t * nwritten , struct gcry_mpi * a ) {
 size_t n ;
 gcry_error_t rc ;
 * buffer = NULL ;
 rc = gcry_mpi_print ( format , NULL , 0 , & n , a ) ;
 if ( rc ) return rc ;
 * buffer = mpi_is_secure ( a ) ? gcry_malloc_secure ( n ? n : 1 ) : gcry_malloc ( n ? n : 1 ) ;
 if ( ! * buffer ) return gpg_error_from_syserror ( ) ;
 rc = gcry_mpi_print ( format , * buffer , n , & n , a ) ;
 if ( rc ) {
 gcry_free ( * buffer ) ;
 * buffer = NULL ;
 }
 else if ( nwritten ) * nwritten = n ;
 return rc ;
 }