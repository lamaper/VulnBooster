gcry_sexp_t _gcry_ecc_get_param_sexp ( const char * name ) {
 gcry_mpi_t pkey [ 6 ] ;
 gcry_sexp_t result ;
 int i ;
 if ( _gcry_ecc_get_param ( name , pkey ) ) return NULL ;
 if ( gcry_sexp_build ( & result , NULL , "(public-key(ecc(p%m)(a%m)(b%m)(g%m)(n%m)))" , pkey [ 0 ] , pkey [ 1 ] , pkey [ 2 ] , pkey [ 3 ] , pkey [ 4 ] ) ) result = NULL ;
 for ( i = 0 ;
 pkey [ i ] ;
 i ++ ) gcry_mpi_release ( pkey [ i ] ) ;
 return result ;
 }