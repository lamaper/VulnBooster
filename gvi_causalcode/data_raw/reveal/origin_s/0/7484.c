void * ps2_mouse_init ( void ( * update_irq ) ( void * , int ) , void * update_arg ) {
 PS2MouseState * s = ( PS2MouseState * ) g_malloc0 ( sizeof ( PS2MouseState ) ) ;
 trace_ps2_mouse_init ( s ) ;
 s -> common . update_irq = update_irq ;
 s -> common . update_arg = update_arg ;
 vmstate_register ( NULL , 0 , & vmstate_ps2_mouse , s ) ;
 qemu_input_handler_register ( ( DeviceState * ) s , & ps2_mouse_handler ) ;
 qemu_register_reset ( ps2_mouse_reset , s ) ;
 return s ;
 }