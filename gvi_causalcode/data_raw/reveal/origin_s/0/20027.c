void ps2_write_keyboard ( void * opaque , int val ) {
 PS2KbdState * s = ( PS2KbdState * ) opaque ;
 trace_ps2_write_keyboard ( opaque , val ) ;
 switch ( s -> common . write_cmd ) {
 default : case - 1 : switch ( val ) {
 case 0x00 : ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 break ;
 case 0x05 : ps2_queue ( & s -> common , KBD_REPLY_RESEND ) ;
 break ;
 case KBD_CMD_GET_ID : ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 ps2_queue ( & s -> common , KBD_REPLY_ID ) ;
 if ( s -> translate ) ps2_queue ( & s -> common , 0x41 ) ;
 else ps2_queue ( & s -> common , 0x83 ) ;
 break ;
 case KBD_CMD_ECHO : ps2_queue ( & s -> common , KBD_CMD_ECHO ) ;
 break ;
 case KBD_CMD_ENABLE : s -> scan_enabled = 1 ;
 ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 break ;
 case KBD_CMD_SCANCODE : case KBD_CMD_SET_LEDS : case KBD_CMD_SET_RATE : s -> common . write_cmd = val ;
 ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 break ;
 case KBD_CMD_RESET_DISABLE : ps2_reset_keyboard ( s ) ;
 s -> scan_enabled = 0 ;
 ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 break ;
 case KBD_CMD_RESET_ENABLE : ps2_reset_keyboard ( s ) ;
 s -> scan_enabled = 1 ;
 ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 break ;
 case KBD_CMD_RESET : ps2_reset_keyboard ( s ) ;
 ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 ps2_queue ( & s -> common , KBD_REPLY_POR ) ;
 break ;
 default : ps2_queue ( & s -> common , KBD_REPLY_RESEND ) ;
 break ;
 }
 break ;
 case KBD_CMD_SCANCODE : if ( val == 0 ) {
 ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 ps2_put_keycode ( s , s -> scancode_set ) ;
 }
 else if ( val >= 1 && val <= 3 ) {
 s -> scancode_set = val ;
 ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 }
 else {
 ps2_queue ( & s -> common , KBD_REPLY_RESEND ) ;
 }
 s -> common . write_cmd = - 1 ;
 break ;
 case KBD_CMD_SET_LEDS : ps2_set_ledstate ( s , val ) ;
 ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 s -> common . write_cmd = - 1 ;
 break ;
 case KBD_CMD_SET_RATE : ps2_queue ( & s -> common , KBD_REPLY_ACK ) ;
 s -> common . write_cmd = - 1 ;
 break ;
 }
 }