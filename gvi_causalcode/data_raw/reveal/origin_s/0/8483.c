void h248_calls_init_tap ( void ) {
 GString * error_string ;
 if ( have_megaco_tap_listener == FALSE ) {
 error_string = register_tap_listener ( "megaco" , & ( the_tapinfo_struct . megaco_dummy ) , NULL , 0 , voip_calls_dlg_reset , h248_calls_packet , voip_calls_dlg_draw ) ;
 if ( error_string != NULL ) {
 simple_dialog ( ESD_TYPE_ERROR , ESD_BTN_OK , "%s" , error_string -> str ) ;
 g_string_free ( error_string , TRUE ) ;
 exit ( 1 ) ;
 }
 have_megaco_tap_listener = TRUE ;
 }
 if ( have_h248_tap_listener == FALSE ) {
 error_string = register_tap_listener ( "h248" , & ( the_tapinfo_struct . h248_dummy ) , NULL , 0 , voip_calls_dlg_reset , h248_calls_packet , voip_calls_dlg_draw ) ;
 if ( error_string != NULL ) {
 simple_dialog ( ESD_TYPE_ERROR , ESD_BTN_OK , "%s" , error_string -> str ) ;
 g_string_free ( error_string , TRUE ) ;
 exit ( 1 ) ;
 }
 have_h248_tap_listener = TRUE ;
 }
 }