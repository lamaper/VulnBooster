static void display_mouse_define ( DisplayChangeListener * dcl , QEMUCursor * c ) {
 SimpleSpiceDisplay * ssd = container_of ( dcl , SimpleSpiceDisplay , dcl ) ;
 qemu_mutex_lock ( & ssd -> lock ) ;
 if ( ssd -> ptr_move ) {
 g_free ( ssd -> ptr_move ) ;
 ssd -> ptr_move = NULL ;
 }
 if ( ssd -> ptr_define ) {
 g_free ( ssd -> ptr_define ) ;
 }
 ssd -> ptr_define = qemu_spice_create_cursor_update ( ssd , c ) ;
 qemu_mutex_unlock ( & ssd -> lock ) ;
 }