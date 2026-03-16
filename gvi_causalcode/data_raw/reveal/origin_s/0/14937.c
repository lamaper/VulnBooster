static void purple_init ( account_t * acc ) {
 char * prpl_id = purple_get_account_prpl_id ( acc ) ;
 PurplePlugin * prpl = purple_plugins_find_with_id ( prpl_id ) ;
 PurplePluginProtocolInfo * pi = prpl -> info -> extra_info ;
 PurpleAccount * pa ;
 GList * i , * st ;
 set_t * s ;
 char help_title [ 64 ] ;
 GString * help ;
 static gboolean dir_fixed = FALSE ;
 if ( ! dir_fixed ) {
 PurpleCertificatePool * pool ;
 irc_t * irc = acc -> bee -> ui_data ;
 char * dir ;
 dir = g_strdup_printf ( "%s/purple/%s" , global . conf -> configdir , irc -> user -> nick ) ;
 purple_util_set_user_dir ( dir ) ;
 g_free ( dir ) ;
 purple_blist_load ( ) ;
 purple_prefs_load ( ) ;
 if ( proxytype == PROXY_SOCKS4A ) {
 purple_prefs_set_bool ( "/purple/proxy/socks4_remotedns" , TRUE ) ;
 }
 pool = purple_certificate_find_pool ( "x509" , "tls_peers" ) ;
 dir = purple_certificate_pool_mkpath ( pool , NULL ) ;
 purple_build_dir ( dir , 0700 ) ;
 g_free ( dir ) ;
 dir_fixed = TRUE ;
 }
 help = g_string_new ( "" ) ;
 g_string_printf ( help , "BitlBee libpurple module %s (%s).\n\nSupported settings:" , ( char * ) acc -> prpl -> name , prpl -> info -> name ) ;
 if ( pi -> user_splits ) {
 GList * l ;
 g_string_append_printf ( help , "\n* username: Username" ) ;
 for ( l = pi -> user_splits ;
 l ;
 l = l -> next ) {
 g_string_append_printf ( help , "%c%s" , purple_account_user_split_get_separator ( l -> data ) , purple_account_user_split_get_text ( l -> data ) ) ;
 }
 }
 for ( i = pi -> protocol_options ;
 i ;
 i = i -> next ) {
 PurpleAccountOption * o = i -> data ;
 const char * name ;
 char * def = NULL ;
 set_eval eval = NULL ;
 void * eval_data = NULL ;
 GList * io = NULL ;
 GSList * opts = NULL ;
 name = purple_account_option_get_setting ( o ) ;
 switch ( purple_account_option_get_type ( o ) ) {
 case PURPLE_PREF_STRING : def = g_strdup ( purple_account_option_get_default_string ( o ) ) ;
 g_string_append_printf ( help , "\n* %s (%s), %s, default: %s" , name , purple_account_option_get_text ( o ) , "string" , def ) ;
 break ;
 case PURPLE_PREF_INT : def = g_strdup_printf ( "%d" , purple_account_option_get_default_int ( o ) ) ;
 eval = set_eval_int ;
 g_string_append_printf ( help , "\n* %s (%s), %s, default: %s" , name , purple_account_option_get_text ( o ) , "integer" , def ) ;
 break ;
 case PURPLE_PREF_BOOLEAN : if ( purple_account_option_get_default_bool ( o ) ) {
 def = g_strdup ( "true" ) ;
 }
 else {
 def = g_strdup ( "false" ) ;
 }
 eval = set_eval_bool ;
 g_string_append_printf ( help , "\n* %s (%s), %s, default: %s" , name , purple_account_option_get_text ( o ) , "boolean" , def ) ;
 break ;
 case PURPLE_PREF_STRING_LIST : def = g_strdup ( purple_account_option_get_default_list_value ( o ) ) ;
 g_string_append_printf ( help , "\n* %s (%s), %s, default: %s" , name , purple_account_option_get_text ( o ) , "list" , def ) ;
 g_string_append ( help , "\n Possible values: " ) ;
 for ( io = purple_account_option_get_list ( o ) ;
 io ;
 io = io -> next ) {
 PurpleKeyValuePair * kv = io -> data ;
 opts = g_slist_append ( opts , kv -> value ) ;
 if ( strcmp ( kv -> value , kv -> key ) != 0 ) {
 g_string_append_printf ( help , "%s (%s), " , ( char * ) kv -> value , kv -> key ) ;
 }
 else {
 g_string_append_printf ( help , "%s, " , ( char * ) kv -> value ) ;
 }
 }
 g_string_truncate ( help , help -> len - 2 ) ;
 eval = set_eval_list ;
 eval_data = opts ;
 break ;
 default : g_string_append_printf ( help , "\n* [%s] UNSUPPORTED (type %d)" , name , purple_account_option_get_type ( o ) ) ;
 name = NULL ;
 }
 if ( name != NULL ) {
 s = set_add ( & acc -> set , name , def , eval , acc ) ;
 s -> flags |= ACC_SET_OFFLINE_ONLY ;
 s -> eval_data = eval_data ;
 g_free ( def ) ;
 }
 }
 g_snprintf ( help_title , sizeof ( help_title ) , "purple %s" , ( char * ) acc -> prpl -> name ) ;
 help_add_mem ( & global . help , help_title , help -> str ) ;
 g_string_free ( help , TRUE ) ;
 s = set_add ( & acc -> set , "display_name" , NULL , set_eval_display_name , acc ) ;
 s -> flags |= ACC_SET_ONLINE_ONLY ;
 if ( pi -> options & OPT_PROTO_MAIL_CHECK ) {
 s = set_add ( & acc -> set , "mail_notifications" , "false" , set_eval_bool , acc ) ;
 s -> flags |= ACC_SET_OFFLINE_ONLY ;
 s = set_add ( & acc -> set , "mail_notifications_handle" , NULL , NULL , acc ) ;
 s -> flags |= ACC_SET_OFFLINE_ONLY | SET_NULL_OK ;
 }
 if ( strcmp ( prpl -> info -> name , "Gadu-Gadu" ) == 0 ) {
 s = set_add ( & acc -> set , "gg_sync_contacts" , "true" , set_eval_bool , acc ) ;
 }
 pa = purple_account_new ( acc -> user , prpl_id ) ;
 for ( st = purple_account_get_status_types ( pa ) ;
 st ;
 st = st -> next ) {
 PurpleStatusPrimitive prim = purple_status_type_get_primitive ( st -> data ) ;
 if ( prim == PURPLE_STATUS_AVAILABLE ) {
 if ( purple_status_type_get_attr ( st -> data , "message" ) ) {
 acc -> flags |= ACC_FLAG_STATUS_MESSAGE ;
 }
 }
 else if ( prim != PURPLE_STATUS_OFFLINE ) {
 if ( purple_status_type_get_attr ( st -> data , "message" ) ) {
 acc -> flags |= ACC_FLAG_AWAY_MESSAGE ;
 }
 }
 }
 purple_accounts_remove ( pa ) ;
 }