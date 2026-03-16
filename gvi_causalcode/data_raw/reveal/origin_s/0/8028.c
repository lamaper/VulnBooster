void mpi_set_cond ( MPI w , MPI u , unsigned long set ) {
 mpi_size_t i ;
 mpi_size_t nlimbs = u -> alloced ;
 mpi_limb_t mask = ( ( mpi_limb_t ) 0 ) - ! ! set ;
 mpi_limb_t x ;
 if ( w -> alloced != u -> alloced ) log_bug ( "mpi_set_cond: different sizes\n" ) ;
 for ( i = 0 ;
 i < nlimbs ;
 i ++ ) {
 x = mask & ( w -> d [ i ] ^ u -> d [ i ] ) ;
 w -> d [ i ] = w -> d [ i ] ^ x ;
 }
 x = mask & ( w -> nlimbs ^ u -> nlimbs ) ;
 w -> nlimbs = w -> nlimbs ^ x ;
 x = mask & ( w -> nbits ^ u -> nbits ) ;
 w -> nbits = w -> nbits ^ x ;
 x = mask & ( w -> sign ^ u -> sign ) ;
 w -> sign = w -> sign ^ x ;
 }