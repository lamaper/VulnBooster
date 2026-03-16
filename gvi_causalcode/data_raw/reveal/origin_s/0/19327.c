void mpi_set ( MPI w , MPI u ) {
 mpi_ptr_t wp , up ;
 mpi_size_t usize = u -> nlimbs ;
 int usign = u -> sign ;
 RESIZE_IF_NEEDED ( w , usize ) ;
 wp = w -> d ;
 up = u -> d ;
 MPN_COPY ( wp , up , usize ) ;
 w -> nlimbs = usize ;
 w -> nbits = u -> nbits ;
 w -> flags = u -> flags ;
 w -> sign = usign ;
 }