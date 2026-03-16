void remove_tap_listener_h248_calls ( void ) {
 remove_tap_listener ( & ( the_tapinfo_struct . h248_dummy ) ) ;
 remove_tap_listener ( & ( the_tapinfo_struct . megaco_dummy ) ) ;
 have_megaco_tap_listener = FALSE ;
 have_h248_tap_listener = FALSE ;
 }