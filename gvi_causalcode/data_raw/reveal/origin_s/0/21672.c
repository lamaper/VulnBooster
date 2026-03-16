static void mips_pica61_init ( QEMUMachineInitArgs * args ) {
 ram_addr_t ram_size = args -> ram_size ;
 const char * cpu_model = args -> cpu_model ;
 mips_jazz_init ( get_system_memory ( ) , get_system_io ( ) , ram_size , cpu_model , JAZZ_PICA61 ) ;
 }