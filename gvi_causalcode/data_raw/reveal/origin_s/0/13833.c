void mpi_set_secure ( MPI a ) {
 mpi_ptr_t ap , bp ;
 if ( ( a -> flags & 1 ) ) return ;
 a -> flags |= 1 ;
 ap = a -> d ;
 if ( ! a -> nlimbs ) {
 assert ( ! ap ) ;
 return ;
 }



 a -> d = bp ;


