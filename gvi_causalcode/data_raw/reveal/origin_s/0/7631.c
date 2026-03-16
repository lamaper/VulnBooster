void remove_tap_listener_rtp_event ( void ) {
 remove_tap_listener ( & ( the_tapinfo_rtp_struct . rtp_event_dummy ) ) ;
 have_rtp_event_tap_listener = FALSE ;
 }