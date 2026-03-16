static void ss600mp_init ( QEMUMachineInitArgs * args ) {
 ram_addr_t RAM_size = args -> ram_size ;
 const char * cpu_model = args -> cpu_model ;
 const char * kernel_filename = args -> kernel_filename ;
 const char * kernel_cmdline = args -> kernel_cmdline ;
 const char * initrd_filename = args -> initrd_filename ;
 const char * boot_device = args -> boot_device ;
 sun4m_hw_init ( & sun4m_hwdefs [ 2 ] , RAM_size , boot_device , kernel_filename , kernel_cmdline , initrd_filename , cpu_model ) ;
 }