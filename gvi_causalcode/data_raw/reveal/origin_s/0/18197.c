static void nvic_sysreg_write ( void * opaque , hwaddr addr , uint64_t value , unsigned size ) {
 nvic_state * s = ( nvic_state * ) opaque ;
 uint32_t offset = addr ;
 int i ;
 switch ( offset ) {
 case 0xd18 ... 0xd23 : for ( i = 0 ;
 i < size ;
 i ++ ) {
 s -> gic . priority1 [ ( offset - 0xd14 ) + i ] [ 0 ] = ( value >> ( i * 8 ) ) & 0xff ;
 }
 gic_update ( & s -> gic ) ;
 return ;
 }
 if ( size == 4 ) {
 nvic_writel ( s , offset , value ) ;
 return ;
 }
 qemu_log_mask ( LOG_GUEST_ERROR , "NVIC: Bad write of size %d at offset 0x%x\n" , size , offset ) ;
 }