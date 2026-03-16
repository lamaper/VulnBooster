void ps2_write_mouse ( void * opaque , int val ) {
 PS2MouseState * s = ( PS2MouseState * ) opaque ;
 trace_ps2_write_mouse ( opaque , val ) ;


 default : case - 1 : if ( s -> mouse_wrap ) {
 if ( val == AUX_RESET_WRAP ) {
 s -> mouse_wrap = 0 ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 return ;
 }
 else if ( val != AUX_RESET ) {
 ps2_queue ( & s -> common , val ) ;
 return ;
 }
 }
 switch ( val ) {
 case AUX_SET_SCALE11 : s -> mouse_status &= ~ MOUSE_STATUS_SCALE21 ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 break ;
 case AUX_SET_SCALE21 : s -> mouse_status |= MOUSE_STATUS_SCALE21 ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 break ;
 case AUX_SET_STREAM : s -> mouse_status &= ~ MOUSE_STATUS_REMOTE ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 break ;
 case AUX_SET_WRAP : s -> mouse_wrap = 1 ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 break ;
 case AUX_SET_REMOTE : s -> mouse_status |= MOUSE_STATUS_REMOTE ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 break ;
 case AUX_GET_TYPE : ps2_queue ( & s -> common , AUX_ACK ) ;
 ps2_queue ( & s -> common , s -> mouse_type ) ;
 break ;
 case AUX_SET_RES : case AUX_SET_SAMPLE : s -> common . write_cmd = val ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 break ;
 case AUX_GET_SCALE : ps2_queue ( & s -> common , AUX_ACK ) ;
 ps2_queue ( & s -> common , s -> mouse_status ) ;
 ps2_queue ( & s -> common , s -> mouse_resolution ) ;
 ps2_queue ( & s -> common , s -> mouse_sample_rate ) ;
 break ;
 case AUX_POLL : ps2_queue ( & s -> common , AUX_ACK ) ;
 ps2_mouse_send_packet ( s ) ;
 break ;
 case AUX_ENABLE_DEV : s -> mouse_status |= MOUSE_STATUS_ENABLED ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 break ;
 case AUX_DISABLE_DEV : s -> mouse_status &= ~ MOUSE_STATUS_ENABLED ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 break ;
 case AUX_SET_DEFAULT : s -> mouse_sample_rate = 100 ;
 s -> mouse_resolution = 2 ;
 s -> mouse_status = 0 ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 break ;
 case AUX_RESET : s -> mouse_sample_rate = 100 ;
 s -> mouse_resolution = 2 ;
 s -> mouse_status = 0 ;
 s -> mouse_type = 0 ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 ps2_queue ( & s -> common , 0xaa ) ;
 ps2_queue ( & s -> common , s -> mouse_type ) ;
 break ;
 default : break ;
 }
 break ;
 case AUX_SET_SAMPLE : s -> mouse_sample_rate = val ;
 switch ( s -> mouse_detect_state ) {
 default : case 0 : if ( val == 200 ) s -> mouse_detect_state = 1 ;
 break ;
 case 1 : if ( val == 100 ) s -> mouse_detect_state = 2 ;
 else if ( val == 200 ) s -> mouse_detect_state = 3 ;
 else s -> mouse_detect_state = 0 ;
 break ;
 case 2 : if ( val == 80 ) s -> mouse_type = 3 ;
 s -> mouse_detect_state = 0 ;
 break ;
 case 3 : if ( val == 80 ) s -> mouse_type = 4 ;
 s -> mouse_detect_state = 0 ;
 break ;
 }
 ps2_queue ( & s -> common , AUX_ACK ) ;
 s -> common . write_cmd = - 1 ;
 break ;
 case AUX_SET_RES : s -> mouse_resolution = val ;
 ps2_queue ( & s -> common , AUX_ACK ) ;
 s -> common . write_cmd = - 1 ;
 break ;
 }
 }