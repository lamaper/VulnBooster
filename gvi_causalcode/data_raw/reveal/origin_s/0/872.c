gs_ref_memory_t * ialloc_alloc_state ( gs_memory_t * parent , uint clump_size ) {
 clump_t * cp ;
 gs_ref_memory_t * iimem = ialloc_solo ( parent , & st_ref_memory , & cp ) ;
 if ( iimem == 0 ) return 0 ;
 iimem -> stable_memory = ( gs_memory_t * ) iimem ;
 iimem -> procs = gs_ref_memory_procs ;
 iimem -> gs_lib_ctx = parent -> gs_lib_ctx ;
 iimem -> non_gc_memory = parent ;
 iimem -> thread_safe_memory = parent -> thread_safe_memory ;
 iimem -> clump_size = clump_size ;



 iimem -> gc_status . vm_threshold = clump_size * 3L ;
 iimem -> gc_status . max_vm = max_long ;
 iimem -> gc_status . signal_value = 0 ;
 iimem -> gc_status . enabled = false ;
 iimem -> gc_status . requested = 0 ;
 iimem -> gc_allocated = 0 ;
 iimem -> previous_status . allocated = 0 ;
 iimem -> previous_status . used = 0 ;
 ialloc_reset ( iimem ) ;
 iimem -> root = cp ;
 ialloc_set_limit ( iimem ) ;
 iimem -> cc = NULL ;
 iimem -> save_level = 0 ;
 iimem -> new_mask = 0 ;
 iimem -> test_mask = ~ 0 ;
 iimem -> streams = 0 ;
 iimem -> names_array = 0 ;
 iimem -> roots = 0 ;
 iimem -> num_contexts = 0 ;
 iimem -> saved = 0 ;
 return iimem ;
 }