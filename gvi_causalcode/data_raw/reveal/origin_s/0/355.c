unsigned int mpi_nlimb_hint_from_nbits ( unsigned int nbits ) {
 return ( nbits + BITS_PER_MPI_LIMB - 1 ) / BITS_PER_MPI_LIMB ;
 }