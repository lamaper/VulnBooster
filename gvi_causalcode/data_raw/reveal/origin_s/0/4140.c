static void ps2_common_reset ( PS2State * s ) {
 s -> write_cmd = - 1 ;
 ps2_reset_queue ( s ) ;
 s -> update_irq ( s -> update_arg , 0 ) ;
 }