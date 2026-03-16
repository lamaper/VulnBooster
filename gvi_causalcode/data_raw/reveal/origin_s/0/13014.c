static void ps2_reset_queue ( PS2State * s ) {
 PS2Queue * q = & s -> queue ;
 q -> rptr = 0 ;
 q -> wptr = 0 ;
 q -> count = 0 ;
 }