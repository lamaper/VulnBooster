void sccp_calls_init_tap ( void ) {
 GString * error_string ;
 if ( have_sccp_tap_listener == FALSE ) {
 error_string = register_tap_listener ( "sccp" , & ( the_tapinfo_struct . sccp_dummy ) , NULL , 0 , voip_calls_dlg_reset , sccp_calls_packet , voip_calls_dlg_draw ) ;
 if ( error_string != NULL ) {
 simple_dialog ( ESD_TYPE_ERROR , ESD_BTN_OK , "%s" , error_string -> str ) ;
 g_string_free ( error_string , TRUE ) ;
 exit ( 1 ) ;
 }
 have_sccp_tap_listener = TRUE ;
 }
 if ( have_sua_tap_listener == FALSE ) {
 error_string = register_tap_listener ( "sua" , & ( the_tapinfo_struct . sua_dummy ) , NULL , 0 , voip_calls_dlg_reset , sua_calls_packet , voip_calls_dlg_draw ) ;
 if ( error_string != NULL ) {
 simple_dialog ( ESD_TYPE_ERROR , ESD_BTN_OK , "%s" , error_string -> str ) ;
 g_string_free ( error_string , TRUE ) ;
 exit ( 1 ) ;
 }
 have_sua_tap_listener = TRUE ;
 }
 }