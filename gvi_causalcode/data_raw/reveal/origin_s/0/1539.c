void remove_tap_listener_isup_calls ( void ) {
 remove_tap_listener ( & ( the_tapinfo_struct . isup_dummy ) ) ;
 have_isup_tap_listener = FALSE ;
 }