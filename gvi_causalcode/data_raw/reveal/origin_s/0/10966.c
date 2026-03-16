static void rtc_write ( void * opaque , hwaddr addr , uint64_t val , unsigned size ) {
 cpu_outw ( 0x71 , val & 0xff ) ;
 }