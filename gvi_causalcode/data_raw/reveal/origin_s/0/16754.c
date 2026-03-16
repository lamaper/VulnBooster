static uint32_t gic_cpu_read ( GICState * s , int cpu , int offset ) {
 switch ( offset ) {
 case 0x00 : return s -> cpu_enabled [ cpu ] ;
 case 0x04 : return s -> priority_mask [ cpu ] ;
 case 0x08 : return 0 ;
 case 0x0c : return gic_acknowledge_irq ( s , cpu ) ;
 case 0x14 : return s -> running_priority [ cpu ] ;
 case 0x18 : return s -> current_pending [ cpu ] ;
 default : qemu_log_mask ( LOG_GUEST_ERROR , "gic_cpu_read: Bad offset %x\n" , ( int ) offset ) ;
 return 0 ;
 }
 }