static int ps2_kbd_ledstate_post_load ( void * opaque , int version_id ) {
 PS2KbdState * s = opaque ;
 kbd_put_ledstate ( s -> ledstate ) ;
 return 0 ;
 }