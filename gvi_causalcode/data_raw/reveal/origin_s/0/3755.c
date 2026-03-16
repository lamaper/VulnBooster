static uint32_t _PPC_ioB_read ( target_phys_addr_t addr ) {
 uint32_t retval = 0 ;
 if ( addr == 0xBFFFFFF0 ) retval = pic_intack_read ( NULL ) ;
 return retval ;
 }