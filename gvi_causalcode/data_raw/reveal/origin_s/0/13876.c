void ialloc_reset ( gs_ref_memory_t * mem ) {
 mem -> root = 0 ;
 mem -> cc = NULL ;
 mem -> allocated = 0 ;
 mem -> changes = 0 ;
 mem -> scan_limit = 0 ;
 mem -> total_scanned = 0 ;
 mem -> total_scanned_after_compacting = 0 ;
 ialloc_reset_free ( mem ) ;
 }