static int ps2_kbd_pre_save ( void * opaque ) {
 PS2KbdState * s = ( PS2KbdState * ) opaque ;
 PS2State * ps2 = & s -> common ;
 ps2_common_post_load ( ps2 ) ;
 return 0 ;
 }