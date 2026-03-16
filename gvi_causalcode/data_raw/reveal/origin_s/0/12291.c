static void ps2_mouse_reset ( void * opaque ) {
 PS2MouseState * s = ( PS2MouseState * ) opaque ;
 trace_ps2_mouse_reset ( opaque ) ;
 ps2_common_reset ( & s -> common ) ;
 s -> mouse_status = 0 ;
 s -> mouse_resolution = 0 ;
 s -> mouse_sample_rate = 0 ;
 s -> mouse_wrap = 0 ;
 s -> mouse_type = 0 ;
 s -> mouse_detect_state = 0 ;
 s -> mouse_dx = 0 ;
 s -> mouse_dy = 0 ;
 s -> mouse_dz = 0 ;
 s -> mouse_buttons = 0 ;
 }