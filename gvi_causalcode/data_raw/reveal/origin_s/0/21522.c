static void prplcb_conn_progress ( PurpleConnection * gc , const char * text , size_t step , size_t step_count ) {
 struct im_connection * ic = purple_ic_by_gc ( gc ) ;
 imcb_log ( ic , "%s" , text ) ;
 }