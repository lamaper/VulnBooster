void rtp_event_init_tap ( void ) {
 GString * error_string ;
 if ( have_rtp_event_tap_listener == FALSE ) {
 error_string = register_tap_listener ( "rtpevent" , & ( the_tapinfo_rtp_struct . rtp_event_dummy ) , NULL , 0 , NULL , rtp_event_packet , NULL ) ;
 if ( error_string != NULL ) {
 simple_dialog ( ESD_TYPE_ERROR , ESD_BTN_OK , "%s" , error_string -> str ) ;
 g_string_free ( error_string , TRUE ) ;
 exit ( 1 ) ;
 }
 have_rtp_event_tap_listener = TRUE ;
 }
 }