static void ps2_mouse_send_packet ( PS2MouseState * s ) {
 unsigned int b ;
 int dx1 , dy1 , dz1 ;
 dx1 = s -> mouse_dx ;
 dy1 = s -> mouse_dy ;
 dz1 = s -> mouse_dz ;
 if ( dx1 > 127 ) dx1 = 127 ;
 else if ( dx1 < - 127 ) dx1 = - 127 ;
 if ( dy1 > 127 ) dy1 = 127 ;
 else if ( dy1 < - 127 ) dy1 = - 127 ;
 b = 0x08 | ( ( dx1 < 0 ) << 4 ) | ( ( dy1 < 0 ) << 5 ) | ( s -> mouse_buttons & 0x07 ) ;
 ps2_queue ( & s -> common , b ) ;
 ps2_queue ( & s -> common , dx1 & 0xff ) ;
 ps2_queue ( & s -> common , dy1 & 0xff ) ;
 switch ( s -> mouse_type ) {
 default : break ;
 case 3 : if ( dz1 > 127 ) dz1 = 127 ;
 else if ( dz1 < - 127 ) dz1 = - 127 ;
 ps2_queue ( & s -> common , dz1 & 0xff ) ;
 break ;
 case 4 : if ( dz1 > 7 ) dz1 = 7 ;
 else if ( dz1 < - 7 ) dz1 = - 7 ;
 b = ( dz1 & 0x0f ) | ( ( s -> mouse_buttons & 0x18 ) << 1 ) ;
 ps2_queue ( & s -> common , b ) ;
 break ;
 }
 trace_ps2_mouse_send_packet ( s , dx1 , dy1 , dz1 , b ) ;
 s -> mouse_dx -= dx1 ;
 s -> mouse_dy -= dy1 ;
 s -> mouse_dz -= dz1 ;
 }