static void purple_login ( account_t * acc ) {
 struct im_connection * ic = imcb_new ( acc ) ;
 struct purple_data * pd ;
 if ( ( local_bee != NULL && local_bee != acc -> bee ) || ( global . conf -> runmode == RUNMODE_DAEMON && ! getenv ( "BITLBEE_DEBUG" ) ) ) {
 imcb_error ( ic , "Daemon mode detected. Do *not* try to use libpurple in daemon mode! " "Please use inetd or ForkDaemon mode instead." ) ;
 imc_logout ( ic , FALSE ) ;
 return ;
 }
 local_bee = acc -> bee ;
 purple_connections = g_slist_prepend ( purple_connections , ic ) ;
 ic -> proto_data = pd = g_new0 ( struct purple_data , 1 ) ;
 pd -> account = purple_account_new ( acc -> user , purple_get_account_prpl_id ( acc ) ) ;
 pd -> input_requests = g_hash_table_new_full ( g_direct_hash , g_direct_equal , NULL , g_free ) ;
 pd -> next_request_id = 0 ;
 purple_account_set_password ( pd -> account , acc -> pass ) ;
 purple_sync_settings ( acc , pd -> account ) ;
 purple_account_set_enabled ( pd -> account , "BitlBee" , TRUE ) ;
 if ( set_getbool ( & acc -> set , "mail_notifications" ) && set_getstr ( & acc -> set , "mail_notifications_handle" ) ) {
 imcb_add_buddy ( ic , set_getstr ( & acc -> set , "mail_notifications_handle" ) , NULL ) ;
 }
 }