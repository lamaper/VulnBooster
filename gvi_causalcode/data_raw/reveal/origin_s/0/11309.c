void mpi_assign_limb_space ( MPI a , mpi_ptr_t ap , unsigned nlimbs ) {
 mpi_free_limb_space ( a -> d ) ;
 a -> d = ap ;
 a -> alloced = nlimbs ;
 }