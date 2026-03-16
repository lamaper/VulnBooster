static void ps2_kbd_reset ( void * opaque ) {
 PS2KbdState * s = ( PS2KbdState * ) opaque ;
 trace_ps2_kbd_reset ( opaque ) ;
 ps2_common_reset ( & s -> common ) ;
 s -> scan_enabled = 0 ;
 s -> translate = 0 ;
 s -> scancode_set = 2 ;
 s -> modifiers = 0 ;
 }