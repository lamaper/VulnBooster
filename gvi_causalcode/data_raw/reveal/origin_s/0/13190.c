void * mpi_get_opaque ( MPI a , unsigned int * len ) {
 if ( ! ( a -> flags & 4 ) ) log_bug ( "mpi_get_opaque on normal mpi\n" ) ;
 if ( len ) * len = a -> nbits ;
 return a -> d ;
 }