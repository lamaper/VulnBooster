void h245dg_calls_init_tap ( void ) {
 GString * error_string ;
 if ( have_H245dg_tap_listener == FALSE ) {
 error_string = register_tap_listener ( "h245dg" , & ( the_tapinfo_struct . h245dg_dummy ) , NULL , 0 , voip_calls_dlg_reset , H245dgcalls_packet , voip_calls_dlg_draw ) ;
 if ( error_string != NULL ) {
 simple_dialog ( ESD_TYPE_ERROR , ESD_BTN_OK , "%s" , error_string -> str ) ;
 g_string_free ( error_string , TRUE ) ;
 exit ( 1 ) ;
 }
 have_H245dg_tap_listener = TRUE ;
 }
 }