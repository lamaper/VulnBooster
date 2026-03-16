void remove_tap_listener_iax2_calls ( void ) {
 remove_tap_listener ( & ( the_tapinfo_struct . iax2_dummy ) ) ;
 have_iax2_tap_listener = FALSE ;
 }