void remove_tap_listener_q931_calls ( void ) {
 remove_tap_listener ( & ( the_tapinfo_struct . q931_dummy ) ) ;
 have_q931_tap_listener = FALSE ;
 }