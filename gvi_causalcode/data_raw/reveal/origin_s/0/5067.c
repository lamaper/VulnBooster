static void prplcb_conn_report_disconnect_reason ( PurpleConnection * gc , PurpleConnectionError reason , const char * text ) {
 struct im_connection * ic = purple_ic_by_gc ( gc ) ;
 if ( ic != NULL ) {
 imcb_error ( ic , "%s" , text ) ;
 }
 }