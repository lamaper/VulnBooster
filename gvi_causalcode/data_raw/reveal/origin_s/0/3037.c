void # ifdef M_DEBUG mpi_debug_resize ( MPI a , unsigned nlimbs , const char * info ) # else mpi_resize ( MPI a , unsigned nlimbs ) # endif {
 if ( nlimbs <= a -> alloced ) return ;

 else a -> d = m_debug_alloc_clear ( nlimbs * sizeof ( mpi_limb_t ) , info ) ;

 else a -> d = xmalloc_clear ( nlimbs * sizeof ( mpi_limb_t ) ) ;

 }