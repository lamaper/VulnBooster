static void ps2_set_ledstate ( PS2KbdState * s , int ledstate ) {
 trace_ps2_set_ledstate ( s , ledstate ) ;
 s -> ledstate = ledstate ;
 kbd_put_ledstate ( ledstate ) ;
 }