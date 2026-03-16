static void patch_call ( VAPICROMState * s , CPUX86State * env , target_ulong ip , uint32_t target ) {
 uint32_t offset ;
 offset = cpu_to_le32 ( target - ip - 5 ) ;
 patch_byte ( env , ip , 0xe8 ) ;
 cpu_memory_rw_debug ( env , ip + 1 , ( void * ) & offset , sizeof ( offset ) , 1 ) ;
 }