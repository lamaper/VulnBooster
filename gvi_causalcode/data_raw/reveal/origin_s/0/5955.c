static void gic_cpu_write ( GICState * s , int cpu , int offset , uint32_t value ) {
 switch ( offset ) {
 case 0x00 : s -> cpu_enabled [ cpu ] = ( value & 1 ) ;
 DPRINTF ( "CPU %d %sabled\n" , cpu , s -> cpu_enabled [ cpu ] ? "En" : "Dis" ) ;
 break ;
 case 0x04 : s -> priority_mask [ cpu ] = ( value & 0xff ) ;
 break ;
 case 0x08 : break ;
 case 0x10 : return gic_complete_irq ( s , cpu , value & 0x3ff ) ;
 default : qemu_log_mask ( LOG_GUEST_ERROR , "gic_cpu_write: Bad offset %x\n" , ( int ) offset ) ;
 return ;
 }
 gic_update ( s ) ;
 }