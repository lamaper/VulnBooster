static ulong compute_free_objects ( gs_ref_memory_t * mem ) {
 ulong unused = mem -> lost . objects ;
 int i ;
 for ( i = 0 ;
 i < num_freelists ;
 i ++ ) {
 const obj_header_t * pfree ;
 for ( pfree = mem -> freelists [ i ] ;
 pfree != 0 ;
 pfree = * ( const obj_header_t * const * ) pfree ) unused += obj_align_round ( pfree [ - 1 ] . o_size ) ;
 }
 return unused ;
 }