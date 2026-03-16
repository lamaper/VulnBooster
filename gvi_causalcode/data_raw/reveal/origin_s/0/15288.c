static bool ps2_keyboard_ledstate_needed ( void * opaque ) {
 PS2KbdState * s = opaque ;
 return s -> ledstate != 0 ;
 }