MPI # ifdef M_DEBUG mpi_debug_alloc_secure ( unsigned nlimbs , const char * info ) # else mpi_alloc_secure ( unsigned nlimbs ) # endif {
 MPI a ;
 if ( DBG_MEMORY ) log_debug ( "mpi_alloc_secure(%u)\n" , nlimbs * BITS_PER_MPI_LIMB ) ;

 a -> d = nlimbs ? mpi_debug_alloc_limb_space ( nlimbs , 1 , info ) : NULL ;

 a -> d = nlimbs ? mpi_alloc_limb_space ( nlimbs , 1 ) : NULL ;

 a -> flags = 1 ;
 a -> nlimbs = 0 ;
 a -> sign = 0 ;
 a -> nbits = 0 ;
 return a ;
 }