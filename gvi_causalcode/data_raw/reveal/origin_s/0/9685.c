static int ps2_mouse_post_load ( void * opaque , int version_id ) {
 PS2MouseState * s = ( PS2MouseState * ) opaque ;
 PS2State * ps2 = & s -> common ;
 ps2_common_post_load ( ps2 ) ;
 return 0 ;
 }