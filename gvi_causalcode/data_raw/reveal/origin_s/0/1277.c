static void prplcb_conn_disconnected ( PurpleConnection * gc ) {
 struct im_connection * ic = purple_ic_by_gc ( gc ) ;
 if ( ic != NULL ) {
 imc_logout ( ic , ! gc -> wants_to_die ) ;
 }
 }