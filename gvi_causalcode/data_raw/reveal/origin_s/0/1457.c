void ps2_keyboard_set_translation ( void * opaque , int mode ) {
 PS2KbdState * s = ( PS2KbdState * ) opaque ;
 trace_ps2_keyboard_set_translation ( opaque , mode ) ;
 s -> translate = mode ;
 }