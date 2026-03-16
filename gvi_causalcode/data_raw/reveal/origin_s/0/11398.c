static bool ps2_keyboard_need_high_bit_needed ( void * opaque ) {
 PS2KbdState * s = opaque ;
 return s -> need_high_bit != 0 ;
 }