MPI mpi_set_opaque ( MPI a , void * p , unsigned int len ) {
 if ( ! a ) {



 if ( a -> flags & 4 ) xfree ( a -> d ) ;
 else {



 a -> d = p ;
 a -> alloced = 0 ;
 a -> nlimbs = 0 ;
 a -> nbits = len ;
 a -> flags = 4 ;
 return a ;
 }