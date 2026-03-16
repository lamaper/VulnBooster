static void release_mpi_array ( gcry_mpi_t * array ) {
 for ( ;
 * array ;
 array ++ ) {
 mpi_free ( * array ) ;
 * array = NULL ;
 }
 }