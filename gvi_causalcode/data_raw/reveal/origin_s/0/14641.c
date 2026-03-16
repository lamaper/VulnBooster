void ialloc_reset_free ( gs_ref_memory_t * mem ) {
 int i ;
 obj_header_t * * p ;
 mem -> lost . objects = 0 ;
 mem -> lost . refs = 0 ;
 mem -> lost . strings = 0 ;
 mem -> cfreed . cp = 0 ;
 for ( i = 0 , p = & mem -> freelists [ 0 ] ;
 i < num_freelists ;
 i ++ , p ++ ) * p = 0 ;
 mem -> largest_free_size = 0 ;
 }