static void ps2_put_keycode ( void * opaque , int keycode ) {
 PS2KbdState * s = opaque ;
 trace_ps2_put_keycode ( opaque , keycode ) ;
 qemu_system_wakeup_request ( QEMU_WAKEUP_REASON_OTHER ) ;
 if ( s -> translate ) {
 if ( keycode == 0xf0 ) {
 s -> need_high_bit = true ;
 }
 else if ( s -> need_high_bit ) {
 ps2_queue ( & s -> common , translate_table [ keycode ] | 0x80 ) ;
 s -> need_high_bit = false ;
 }
 else {
 ps2_queue ( & s -> common , translate_table [ keycode ] ) ;
 }
 }
 else {
 ps2_queue ( & s -> common , keycode ) ;
 }
 }