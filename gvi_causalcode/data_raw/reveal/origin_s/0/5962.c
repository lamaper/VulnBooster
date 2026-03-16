static void i_status ( gs_memory_t * mem , gs_memory_status_t * pstat ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 ulong unused = imem -> lost . refs + imem -> lost . strings ;
 ulong inner = 0 ;
 clump_splay_walker sw ;
 clump_t * cp ;
 alloc_close_clump ( imem ) ;
 for ( cp = clump_splay_walk_init ( & sw , imem ) ;
 cp != NULL ;
 cp = clump_splay_walk_fwd ( & sw ) ) {
 unused += cp -> ctop - cp -> cbot ;
 if ( cp -> outer ) inner += cp -> cend - ( byte * ) cp -> chead ;
 }
 unused += compute_free_objects ( imem ) ;
 pstat -> used = imem -> allocated + inner - unused + imem -> previous_status . used ;
 pstat -> allocated = imem -> allocated + imem -> previous_status . allocated ;
 pstat -> max_used = 0 ;
 pstat -> is_thread_safe = false ;
 }