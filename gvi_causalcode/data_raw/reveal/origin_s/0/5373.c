void rtp_init_tap ( void ) {
 GString * error_string ;
 if ( have_RTP_tap_listener == FALSE ) {
 error_string = register_tap_listener ( "rtp" , & ( the_tapinfo_rtp_struct . rtp_dummy ) , NULL , 0 , voip_rtp_reset , RTP_packet , RTP_packet_draw ) ;
 if ( error_string != NULL ) {
 simple_dialog ( ESD_TYPE_ERROR , ESD_BTN_OK , "%s" , error_string -> str ) ;
 g_string_free ( error_string , TRUE ) ;
 exit ( 1 ) ;
 }
 have_RTP_tap_listener = TRUE ;
 }
 }