static void free_sip_info ( gpointer p ) {
 sip_calls_info_t * si = ( sip_calls_info_t * ) p ;
 g_free ( si -> call_identifier ) ;
 g_free ( si ) ;
 }