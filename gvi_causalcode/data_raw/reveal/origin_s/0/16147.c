mpi_ptr_t # ifdef M_DEBUG mpi_debug_alloc_limb_space ( unsigned nlimbs , int secure , const char * info ) # else mpi_alloc_limb_space ( unsigned nlimbs , int secure ) # endif {
 size_t len = nlimbs * sizeof ( mpi_limb_t ) ;
 mpi_ptr_t p ;
 if ( DBG_MEMORY ) log_debug ( "mpi_alloc_limb_space(%u)\n" , ( unsigned ) len * 8 ) ;

 if ( nlimbs == 5 && unused_limbs_5 ) {
 p = unused_limbs_5 ;
 unused_limbs_5 = * p ;
 return p ;
 }
 else if ( nlimbs == 32 && unused_limbs_32 ) {
 p = unused_limbs_32 ;
 unused_limbs_32 = * p ;
 return p ;
 }
 else if ( nlimbs == 64 && unused_limbs_64 ) {
 p = unused_limbs_64 ;
 unused_limbs_64 = * p ;
 return p ;
 }
 }



 }