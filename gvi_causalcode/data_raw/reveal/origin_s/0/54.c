static void prplcb_conn_notice ( PurpleConnection * gc , const char * text ) {
 struct im_connection * ic = purple_ic_by_gc ( gc ) ;
 if ( ic != NULL ) {
 imcb_log ( ic , "%s" , text ) ;
 }
 }