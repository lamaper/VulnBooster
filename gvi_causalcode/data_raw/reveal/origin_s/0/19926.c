void remove_tap_listener_h225_calls ( void ) {
 remove_tap_listener ( & ( the_tapinfo_struct . h225_dummy ) ) ;
 have_H225_tap_listener = FALSE ;
 }