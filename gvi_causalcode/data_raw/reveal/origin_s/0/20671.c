static unsigned long sun4m_load_kernel ( const char * kernel_filename , const char * initrd_filename , ram_addr_t RAM_size ) {
 int linux_boot ;
 unsigned int i ;
 long initrd_size , kernel_size ;
 uint8_t * ptr ;
 linux_boot = ( kernel_filename != NULL ) ;
 kernel_size = 0 ;
 if ( linux_boot ) {
 int bswap_needed ;



 if ( kernel_size < 0 ) kernel_size = load_aout ( kernel_filename , KERNEL_LOAD_ADDR , RAM_size - KERNEL_LOAD_ADDR , bswap_needed , TARGET_PAGE_SIZE ) ;
 if ( kernel_size < 0 ) kernel_size = load_image_targphys ( kernel_filename , KERNEL_LOAD_ADDR , RAM_size - KERNEL_LOAD_ADDR ) ;
 if ( kernel_size < 0 ) {
 fprintf ( stderr , "qemu: could not load kernel '%s'\n" , kernel_filename ) ;
 exit ( 1 ) ;
 }
 initrd_size = 0 ;
 if ( initrd_filename ) {
 initrd_size = load_image_targphys ( initrd_filename , INITRD_LOAD_ADDR , RAM_size - INITRD_LOAD_ADDR ) ;
 if ( initrd_size < 0 ) {
 fprintf ( stderr , "qemu: could not load initial ram disk '%s'\n" , initrd_filename ) ;
 exit ( 1 ) ;
 }
 }
 if ( initrd_size > 0 ) {
 for ( i = 0 ;
 i < 64 * TARGET_PAGE_SIZE ;
 i += TARGET_PAGE_SIZE ) {
 ptr = rom_ptr ( KERNEL_LOAD_ADDR + i ) ;
 if ( ldl_p ( ptr ) == 0x48647253 ) {
 stl_p ( ptr + 16 , INITRD_LOAD_ADDR ) ;
 stl_p ( ptr + 20 , initrd_size ) ;
 break ;
 }
 }
 }
 }
 return kernel_size ;
 }