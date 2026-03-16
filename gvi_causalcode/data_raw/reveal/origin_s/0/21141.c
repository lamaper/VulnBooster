void ialloc_free_state ( gs_ref_memory_t * iimem ) {
 clump_t * cp ;
 gs_memory_t * mem ;
 if ( iimem == NULL ) return ;
 cp = iimem -> root ;
 mem = iimem -> non_gc_memory ;
 if ( cp == NULL ) return ;
 gs_free_object ( mem , cp -> chead , "ialloc_solo(allocation failure)" ) ;
 gs_free_object ( mem , cp , "ialloc_solo(allocation failure)" ) ;
 }