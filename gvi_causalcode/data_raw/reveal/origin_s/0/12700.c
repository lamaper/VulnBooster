static void gic_thiscpu_write ( void * opaque , hwaddr addr , uint64_t value , unsigned size ) {
 GICState * s = ( GICState * ) opaque ;
 gic_cpu_write ( s , gic_get_current_cpu ( s ) , addr , value ) ;
 }