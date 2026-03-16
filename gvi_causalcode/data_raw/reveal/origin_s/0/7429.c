static uint64_t rtc_read ( void * opaque , hwaddr addr , unsigned size ) {
 return cpu_inw ( 0x71 ) ;
 }