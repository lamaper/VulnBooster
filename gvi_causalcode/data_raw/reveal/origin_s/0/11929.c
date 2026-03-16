static gcry_err_code_t dummy_verify ( int algorithm , gcry_mpi_t hash , gcry_mpi_t * data , gcry_mpi_t * pkey , int ( * cmp ) ( void * , gcry_mpi_t ) , void * opaquev , int flags , int hashalgo ) {
 ( void ) algorithm ;
 ( void ) hash ;
 ( void ) data ;
 ( void ) pkey ;
 ( void ) cmp ;
 ( void ) opaquev ;
 ( void ) flags ;
 ( void ) hashalgo ;
 fips_signal_error ( "using dummy public key function" ) ;
 return GPG_ERR_NOT_IMPLEMENTED ;
 }