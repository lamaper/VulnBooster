void remove_tap_listener_voip_calls ( void ) {
 remove_tap_listener ( & ( the_tapinfo_struct . voip_dummy ) ) ;
 have_voip_tap_listener = FALSE ;
 }