void remove_tap_listener_mgcp_calls ( void ) {
 remove_tap_listener ( & ( the_tapinfo_struct . mgcp_dummy ) ) ;
 have_MGCP_tap_listener = FALSE ;
 }