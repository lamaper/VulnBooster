static void ps2_mouse_sync ( DeviceState * dev ) {
 PS2MouseState * s = ( PS2MouseState * ) dev ;
 if ( s -> mouse_buttons ) {
 qemu_system_wakeup_request ( QEMU_WAKEUP_REASON_OTHER ) ;
 }
 if ( ! ( s -> mouse_status & MOUSE_STATUS_REMOTE ) ) {
 while ( s -> common . queue . count < PS2_QUEUE_SIZE - 4 ) {
 ps2_mouse_send_packet ( s ) ;
 if ( s -> mouse_dx == 0 && s -> mouse_dy == 0 && s -> mouse_dz == 0 ) break ;
 }
 }
 }