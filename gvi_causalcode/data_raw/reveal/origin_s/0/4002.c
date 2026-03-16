void # ifdef M_DEBUG mpi_debug_free ( MPI a , const char * info ) # else mpi_free ( MPI a ) # endif {
 if ( ! a ) return ;
 if ( DBG_MEMORY ) log_debug ( "mpi_free\n" ) ;
 if ( a -> flags & 4 ) xfree ( a -> d ) ;
 else {



 if ( a -> flags & ~ 7 ) log_bug ( "invalid flag value in mpi\n" ) ;
 xfree ( a ) ;
 }