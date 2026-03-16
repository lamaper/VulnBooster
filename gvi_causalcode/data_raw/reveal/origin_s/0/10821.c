void ialloc_gc_prepare ( gs_ref_memory_t * mem ) {
 while ( mem -> streams != 0 ) {
 stream * s = mem -> streams ;
 mem -> streams = s -> next ;
 s -> prev = s -> next = 0 ;
 }
 }