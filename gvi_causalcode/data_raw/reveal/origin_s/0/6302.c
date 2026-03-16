void # ifdef M_DEBUG mpi_debug_free_limb_space ( mpi_ptr_t a , const char * info ) # else mpi_free_limb_space ( mpi_ptr_t a ) # endif {
 if ( ! a ) return ;
 if ( DBG_MEMORY ) log_debug ( "mpi_free_limb_space of size %lu\n" , ( ulong ) m_size ( a ) * 8 ) ;

 size_t nlimbs = m_size ( a ) / 4 ;
 void * p = a ;
 if ( nlimbs == 5 ) {
 * a = unused_limbs_5 ;
 unused_limbs_5 = a ;
 return ;
 }
 else if ( nlimbs == 32 ) {
 * a = unused_limbs_32 ;
 unused_limbs_32 = a ;
 return ;
 }
 else if ( nlimbs == 64 ) {
 * a = unused_limbs_64 ;
 unused_limbs_64 = a ;
 return ;
 }
 }

 }