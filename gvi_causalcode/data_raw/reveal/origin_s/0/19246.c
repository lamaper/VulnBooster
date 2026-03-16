static int ps2_kbd_post_load ( void * opaque , int version_id ) {
 PS2KbdState * s = ( PS2KbdState * ) opaque ;
 PS2State * ps2 = & s -> common ;
 if ( version_id == 2 ) s -> scancode_set = 2 ;
 ps2_common_post_load ( ps2 ) ;
 return 0 ;
 }