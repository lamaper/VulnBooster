static int ps2_mouse_pre_save ( void * opaque ) {
 PS2MouseState * s = ( PS2MouseState * ) opaque ;
 PS2State * ps2 = & s -> common ;
 ps2_common_post_load ( ps2 ) ;
 return 0 ;
 }