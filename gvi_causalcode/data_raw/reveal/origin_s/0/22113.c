unsigned int mpi_nlimb_hint_from_nbytes ( unsigned int nbytes ) {
 return ( nbytes + BYTES_PER_MPI_LIMB - 1 ) / BYTES_PER_MPI_LIMB ;
 }