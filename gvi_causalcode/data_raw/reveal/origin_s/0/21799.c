static void patch_byte ( CPUX86State * env , target_ulong addr , uint8_t byte ) {
 cpu_memory_rw_debug ( env , addr , & byte , 1 , 1 ) ;
 }