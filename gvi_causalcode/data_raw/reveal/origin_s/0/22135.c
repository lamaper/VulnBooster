static void prplcb_conn_connected ( PurpleConnection * gc ) {
 struct im_connection * ic = purple_ic_by_gc ( gc ) ;
 const char * dn ;
 set_t * s ;
 imcb_connected ( ic ) ;
 if ( ( dn = purple_connection_get_display_name ( gc ) ) && ( s = set_find ( & ic -> acc -> set , "display_name" ) ) ) {
 g_free ( s -> value ) ;
 s -> value = g_strdup ( dn ) ;
 }
 purple_gg_buddylist_import ( gc ) ;
 ic -> flags |= OPT_DOES_HTML ;
 }