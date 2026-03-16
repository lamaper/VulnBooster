static obj_header_t * large_freelist_alloc ( gs_ref_memory_t * mem , uint size ) {
 uint aligned_size = obj_align_round ( size ) ;
 uint aligned_min_size = aligned_size + sizeof ( obj_header_t ) ;
 uint aligned_max_size = aligned_min_size + obj_align_round ( aligned_min_size / 8 ) ;
 obj_header_t * best_fit = 0 ;
 obj_header_t * * best_fit_prev = NULL ;
 uint best_fit_size = max_uint ;
 obj_header_t * pfree ;
 obj_header_t * * ppfprev = & mem -> freelists [ LARGE_FREELIST_INDEX ] ;
 uint largest_size = 0 ;
 if ( aligned_size > mem -> largest_free_size ) return 0 ;
 while ( ( pfree = * ppfprev ) != 0 ) {
 uint free_size = obj_align_round ( pfree [ - 1 ] . o_size ) ;
 if ( free_size == aligned_size || ( free_size >= aligned_min_size && free_size < best_fit_size ) ) {
 best_fit = pfree ;
 best_fit_prev = ppfprev ;
 best_fit_size = pfree [ - 1 ] . o_size ;
 if ( best_fit_size <= aligned_max_size ) break ;
 }
 ppfprev = ( obj_header_t * * ) pfree ;
 if ( free_size > largest_size ) largest_size = free_size ;
 }
 if ( best_fit == 0 ) {
 mem -> largest_free_size = largest_size ;
 return 0 ;
 }
 * best_fit_prev = * ( obj_header_t * * ) best_fit ;
 trim_obj ( mem , best_fit , aligned_size , ( clump_t * ) 0 ) ;
 best_fit [ - 1 ] . o_size = size ;
 return best_fit ;
 }