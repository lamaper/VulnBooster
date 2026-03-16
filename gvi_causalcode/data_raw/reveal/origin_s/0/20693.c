void remove_tap_listener_mtp3_calls ( void ) {
 remove_tap_listener ( & ( the_tapinfo_struct . mtp3_dummy ) ) ;
 remove_tap_listener ( & ( the_tapinfo_struct . m3ua_dummy ) ) ;
 have_mtp3_tap_listener = FALSE ;
 have_m3ua_tap_listener = FALSE ;
 }