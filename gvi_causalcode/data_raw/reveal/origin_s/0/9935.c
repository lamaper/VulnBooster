void ps2_mouse_fake_event ( void * opaque ) {
 PS2MouseState * s = opaque ;
 trace_ps2_mouse_fake_event ( opaque ) ;
 s -> mouse_dx ++ ;
 ps2_mouse_sync ( opaque ) ;
 }