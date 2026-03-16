gcry_mpi_t _gcry_sexp_nth_opaque_mpi ( gcry_sexp_t list , int number ) {
 char * p ;
 size_t n ;
 gcry_mpi_t a ;
 p = gcry_sexp_nth_buffer ( list , number , & n ) ;
 if ( ! p ) return NULL ;
 a = gcry_is_secure ( list ) ? _gcry_mpi_snew ( 0 ) : _gcry_mpi_new ( 0 ) ;
 if ( a ) gcry_mpi_set_opaque ( a , p , n * 8 ) ;
 else gcry_free ( p ) ;
 return a ;
 }