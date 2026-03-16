void q931_calls_init_tap ( void ) {
 GString * error_string ;
 if ( have_q931_tap_listener == FALSE ) {
 error_string = register_tap_listener ( "q931" , & ( the_tapinfo_struct . q931_dummy ) , NULL , 0 , voip_calls_dlg_reset , q931_calls_packet , voip_calls_dlg_draw ) ;
 if ( error_string != NULL ) {
 simple_dialog ( ESD_TYPE_ERROR , ESD_BTN_OK , "%s" , error_string -> str ) ;
 g_string_free ( error_string , TRUE ) ;
 exit ( 1 ) ;
 }
 have_q931_tap_listener = TRUE ;
 }
 }