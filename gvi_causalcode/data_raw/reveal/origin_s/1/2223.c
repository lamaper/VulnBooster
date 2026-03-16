void ppc_prep_init ( int ram_size , int vga_ram_size , int boot_device , DisplayState * ds , const char * * fd_filename , int snapshot , const char * kernel_filename , const char * kernel_cmdline , const char * initrd_filename ) {
 char buf [ 1024 ] ;
 int PPC_io_memory ;
 int ret , linux_boot , initrd_size , i , nb_nics1 , fd ;
 linux_boot = ( kernel_filename != NULL ) ;
 cpu_register_physical_memory ( 0 , ram_size , 0 ) ;
 isa_mem_base = 0xc0000000 ;
 if ( linux_boot ) {
 ret = load_image ( kernel_filename , phys_ram_base + KERNEL_LOAD_ADDR ) ;
 if ( ret < 0 ) {
 fprintf ( stderr , "qemu: could not load kernel '%s'\n" , kernel_filename ) ;
 exit ( 1 ) ;
 }
 initrd_size = 0 ;

 initrd_size = load_image ( initrd_filename , phys_ram_base + INITRD_LOAD_ADDR ) ;
 if ( initrd_size < 0 ) {
 fprintf ( stderr , "qemu: could not load initial ram disk '%s'\n" , initrd_filename ) ;
 exit ( 1 ) ;
 }
 }

 }
 else {
 snprintf ( buf , sizeof ( buf ) , "%s" , BIOS_FILENAME ) ;
 printf ( "load BIOS at %p\n" , phys_ram_base + 0x000f0000 ) ;
 ret = load_image ( buf , phys_ram_base + 0x000f0000 ) ;
 if ( ret != 0x10000 ) {
 fprintf ( stderr , "qemu: could not load PPC bios '%s' (%d)\n%m\n" , buf , ret ) ;
 exit ( 1 ) ;
 }
 }
 vga_initialize ( ds , phys_ram_base + ram_size , ram_size , vga_ram_size ) ;
 rtc_init ( 0x70 , 8 ) ;
 pic_init ( ) ;
 fd = serial_open_device ( ) ;
 serial_init ( 0x3f8 , 4 , fd ) ;

 if ( nb_nics1 > NE2000_NB_MAX ) nb_nics1 = NE2000_NB_MAX ;
 for ( i = 0 ;
 i < nb_nics1 ;
 i ++ ) {
 ne2000_init ( ne2000_io [ i ] , ne2000_irq [ i ] , & nd_table [ i ] ) ;
 }

 i < 2 ;
 i ++ ) {
 ide_init ( ide_iobase [ i ] , ide_iobase2 [ i ] , ide_irq [ i ] , bs_table [ 2 * i ] , bs_table [ 2 * i + 1 ] ) ;
 }
 kbd_init ( ) ;
 AUD_init ( ) ;
 DMA_init ( ) ;
 fdctrl_init ( 6 , 2 , 0 , 0x3f0 , fd_table ) ;
 PPC_io_memory = cpu_register_io_memory ( 0 , PPC_io_read , PPC_io_write ) ;
 cpu_register_physical_memory ( 0x80000000 , 0x10000 , PPC_io_memory ) ;
 register_ioport_read ( 0x398 , 2 , 1 , & PREP_io_read , NULL ) ;
 register_ioport_write ( 0x398 , 2 , 1 , & PREP_io_write , NULL ) ;
 register_ioport_write ( 0x0092 , 0x1 , 1 , & PREP_io_800_writeb , NULL ) ;
 register_ioport_read ( 0x0800 , 0x52 , 1 , & PREP_io_800_readb , NULL ) ;
 register_ioport_write ( 0x0800 , 0x52 , 1 , & PREP_io_800_writeb , NULL ) ;
 PPC_io_memory = cpu_register_io_memory ( 0 , PPC_ioB_read , PPC_ioB_write ) ;
 cpu_register_physical_memory ( 0xBFFFFFF0 , 0x4 , PPC_io_memory ) ;
 prep_NVRAM_init ( ) ;
 PPC_end_init ( ) ;
 }