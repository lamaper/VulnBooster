static void ps2_keyboard_event ( DeviceState * dev , QemuConsole * src , InputEvent * evt ) {
 PS2KbdState * s = ( PS2KbdState * ) dev ;
 InputKeyEvent * key = evt -> u . key . data ;
 int qcode ;
 uint16_t keycode ;
 int mod ;
 qemu_system_wakeup_request ( QEMU_WAKEUP_REASON_OTHER ) ;
 assert ( evt -> type == INPUT_EVENT_KIND_KEY ) ;
 qcode = qemu_input_key_value_to_qcode ( key -> key ) ;
 mod = ps2_modifier_bit ( qcode ) ;
 trace_ps2_keyboard_event ( s , qcode , key -> down , mod , s -> modifiers ) ;
 if ( key -> down ) {
 s -> modifiers |= mod ;
 }
 else {
 s -> modifiers &= ~ mod ;
 }
 if ( s -> scancode_set == 1 ) {
 if ( qcode == Q_KEY_CODE_PAUSE ) {
 if ( s -> modifiers & ( MOD_CTRL_L | MOD_CTRL_R ) ) {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x46 ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xc6 ) ;
 }
 }
 else {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xe1 ) ;
 ps2_put_keycode ( s , 0x1d ) ;
 ps2_put_keycode ( s , 0x45 ) ;
 ps2_put_keycode ( s , 0xe1 ) ;
 ps2_put_keycode ( s , 0x9d ) ;
 ps2_put_keycode ( s , 0xc5 ) ;
 }
 }
 }
 else if ( qcode == Q_KEY_CODE_PRINT ) {
 if ( s -> modifiers & MOD_ALT_L ) {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xb8 ) ;
 ps2_put_keycode ( s , 0x38 ) ;
 ps2_put_keycode ( s , 0x54 ) ;
 }
 else {
 ps2_put_keycode ( s , 0xd4 ) ;
 ps2_put_keycode ( s , 0xb8 ) ;
 ps2_put_keycode ( s , 0x38 ) ;
 }
 }
 else if ( s -> modifiers & MOD_ALT_R ) {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xb8 ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x38 ) ;
 ps2_put_keycode ( s , 0x54 ) ;
 }
 else {
 ps2_put_keycode ( s , 0xd4 ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xb8 ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x38 ) ;
 }
 }
 else if ( s -> modifiers & ( MOD_SHIFT_L | MOD_CTRL_L | MOD_SHIFT_R | MOD_CTRL_R ) ) {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x37 ) ;
 }
 else {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xb7 ) ;
 }
 }
 else {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x2a ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x37 ) ;
 }
 else {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xb7 ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xaa ) ;
 }
 }
 }
 else {
 keycode = qcode_to_keycode_set1 [ qcode ] ;
 if ( keycode ) {
 if ( keycode & 0xff00 ) {
 ps2_put_keycode ( s , keycode >> 8 ) ;
 }
 if ( ! key -> down ) {
 keycode |= 0x80 ;
 }
 ps2_put_keycode ( s , keycode & 0xff ) ;
 }
 else {
 qemu_log_mask ( LOG_UNIMP , "ps2: ignoring key with qcode %d\n" , qcode ) ;
 }
 }
 }
 else if ( s -> scancode_set == 2 ) {
 if ( qcode == Q_KEY_CODE_PAUSE ) {
 if ( s -> modifiers & ( MOD_CTRL_L | MOD_CTRL_R ) ) {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x7e ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x7e ) ;
 }
 }
 else {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xe1 ) ;
 ps2_put_keycode ( s , 0x14 ) ;
 ps2_put_keycode ( s , 0x77 ) ;
 ps2_put_keycode ( s , 0xe1 ) ;
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x14 ) ;
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x77 ) ;
 }
 }
 }
 else if ( qcode == Q_KEY_CODE_PRINT ) {
 if ( s -> modifiers & MOD_ALT_L ) {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x11 ) ;
 ps2_put_keycode ( s , 0x11 ) ;
 ps2_put_keycode ( s , 0x84 ) ;
 }
 else {
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x84 ) ;
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x11 ) ;
 ps2_put_keycode ( s , 0x11 ) ;
 }
 }
 else if ( s -> modifiers & MOD_ALT_R ) {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x11 ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x11 ) ;
 ps2_put_keycode ( s , 0x84 ) ;
 }
 else {
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x84 ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x11 ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x11 ) ;
 }
 }
 else if ( s -> modifiers & ( MOD_SHIFT_L | MOD_CTRL_L | MOD_SHIFT_R | MOD_CTRL_R ) ) {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x7c ) ;
 }
 else {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x7c ) ;
 }
 }
 else {
 if ( key -> down ) {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x12 ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0x7c ) ;
 }
 else {
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x7c ) ;
 ps2_put_keycode ( s , 0xe0 ) ;
 ps2_put_keycode ( s , 0xf0 ) ;
 ps2_put_keycode ( s , 0x12 ) ;
 }
 }
 }
 else {
 keycode = qcode_to_keycode_set2 [ qcode ] ;
 if ( keycode ) {
 if ( keycode & 0xff00 ) {
 ps2_put_keycode ( s , keycode >> 8 ) ;
 }
 if ( ! key -> down ) {
 ps2_put_keycode ( s , 0xf0 ) ;
 }
 ps2_put_keycode ( s , keycode & 0xff ) ;
 }
 else {
 qemu_log_mask ( LOG_UNIMP , "ps2: ignoring key with qcode %d\n" , qcode ) ;
 }
 }
 }
 else if ( s -> scancode_set == 3 ) {
 keycode = qcode_to_keycode_set3 [ qcode ] ;
 if ( keycode ) {
 if ( ! key -> down ) {
 ps2_put_keycode ( s , 0xf0 ) ;
 }
 ps2_put_keycode ( s , keycode ) ;
 }
 else {
 qemu_log_mask ( LOG_UNIMP , "ps2: ignoring key with qcode %d\n" , qcode ) ;
 }
 }
 }