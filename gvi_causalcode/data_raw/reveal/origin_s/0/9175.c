static void read_guest_rom_state ( VAPICROMState * s ) {
 cpu_physical_memory_rw ( s -> rom_state_paddr , ( void * ) & s -> rom_state , sizeof ( GuestROMState ) , 0 ) ;
 }