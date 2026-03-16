void qemu_spice_display_init ( void ) {
 QemuConsole * con ;
 int i ;
 for ( i = 0 ;
 ;
 i ++ ) {
 con = qemu_console_lookup_by_index ( i ) ;
 if ( ! con || ! qemu_console_is_graphic ( con ) ) {
 break ;
 }
 if ( qemu_spice_have_display_interface ( con ) ) {
 continue ;
 }
 qemu_spice_display_init_one ( con ) ;
 }
 }