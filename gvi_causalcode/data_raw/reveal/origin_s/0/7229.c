void remove_tap_listener_sccp_calls ( void ) {
 remove_tap_listener ( & ( the_tapinfo_struct . sccp_dummy ) ) ;
 have_sccp_tap_listener = FALSE ;
 have_sua_tap_listener = FALSE ;
 }