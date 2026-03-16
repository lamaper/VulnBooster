void * ps2_kbd_init ( void ( * update_irq ) ( void * , int ) , void * update_arg ) {
 PS2KbdState * s = ( PS2KbdState * ) g_malloc0 ( sizeof ( PS2KbdState ) ) ;
 trace_ps2_kbd_init ( s ) ;
 s -> common . update_irq = update_irq ;
 s -> common . update_arg = update_arg ;
 s -> scancode_set = 2 ;
 vmstate_register ( NULL , 0 , & vmstate_ps2_keyboard , s ) ;
 qemu_input_handler_register ( ( DeviceState * ) s , & ps2_keyboard_handler ) ;
 qemu_register_reset ( ps2_kbd_reset , s ) ;
 return s ;
 }