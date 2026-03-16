static uint64_t nvic_sysreg_read ( void * opaque , hwaddr addr , unsigned size ) {
 nvic_state * s = ( nvic_state * ) opaque ;
 uint32_t offset = addr ;
 int i ;
 uint32_t val ;
 switch ( offset ) {
 case 0xd18 ... 0xd23 : val = 0 ;
 for ( i = 0 ;
 i < size ;
 i ++ ) {
 val |= s -> gic . priority1 [ ( offset - 0xd14 ) + i ] [ 0 ] << ( i * 8 ) ;
 }
 return val ;
 case 0xfe0 ... 0xfff : if ( offset & 3 ) {
 return 0 ;
 }
 return nvic_id [ ( offset - 0xfe0 ) >> 2 ] ;
 }
 if ( size == 4 ) {
 return nvic_readl ( s , offset ) ;
 }
 qemu_log_mask ( LOG_GUEST_ERROR , "NVIC: Bad read of size %d at offset 0x%x\n" , size , offset ) ;
 return 0 ;
 }