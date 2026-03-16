static uint64_t gic_thiscpu_read ( void * opaque , hwaddr addr , unsigned size ) {
 GICState * s = ( GICState * ) opaque ;
 return gic_cpu_read ( s , gic_get_current_cpu ( s ) , addr ) ;
 }