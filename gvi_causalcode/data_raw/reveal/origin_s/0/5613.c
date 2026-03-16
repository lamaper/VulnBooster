void remove_tap_listener_sip_calls ( void ) {
 remove_tap_listener ( & ( the_tapinfo_struct . sip_dummy ) ) ;
 have_SIP_tap_listener = FALSE ;
 }