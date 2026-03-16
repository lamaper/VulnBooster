MPI # ifdef M_DEBUG mpi_debug_copy ( MPI a , const char * info ) # else mpi_copy ( MPI a ) # endif {
 int i ;
 MPI b ;
 if ( a && ( a -> flags & 4 ) ) {
 void * p = m_is_secure ( a -> d ) ? xmalloc_secure ( a -> nbits ) : xmalloc ( a -> nbits ) ;
 memcpy ( p , a -> d , a -> nbits ) ;
 b = mpi_set_opaque ( NULL , p , a -> nbits ) ;
 }
 else if ( a ) {



 b -> sign = a -> sign ;
 b -> flags = a -> flags ;
 b -> nbits = a -> nbits ;
 for ( i = 0 ;
 i < b -> nlimbs ;
 i ++ ) b -> d [ i ] = a -> d [ i ] ;
 }
 else b = NULL ;
 return b ;
 }