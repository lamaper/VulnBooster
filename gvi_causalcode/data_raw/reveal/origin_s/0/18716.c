void purple_initmodule ( ) {
 struct prpl funcs ;
 GList * prots ;
 GString * help ;
 char * dir ;
 if ( purple_get_core ( ) != NULL ) {
 log_message ( LOGLVL_ERROR , "libpurple already initialized. " "Please use inetd or ForkDaemon mode instead." ) ;
 return ;
 }
 g_assert ( ( int ) B_EV_IO_READ == ( int ) PURPLE_INPUT_READ ) ;
 g_assert ( ( int ) B_EV_IO_WRITE == ( int ) PURPLE_INPUT_WRITE ) ;
 dir = g_strdup_printf ( "%s/purple" , global . conf -> configdir ) ;
 purple_util_set_user_dir ( dir ) ;
 g_free ( dir ) ;
 dir = g_strdup_printf ( "%s/purple" , global . conf -> plugindir ) ;
 purple_plugins_add_search_path ( dir ) ;
 g_free ( dir ) ;
 purple_debug_set_enabled ( FALSE ) ;
 purple_core_set_ui_ops ( & bee_core_uiops ) ;
 purple_eventloop_set_ui_ops ( & glib_eventloops ) ;
 if ( ! purple_core_init ( "BitlBee" ) ) {
 fprintf ( stderr , "libpurple initialization failed.\n" ) ;
 abort ( ) ;
 }
 if ( proxytype != PROXY_NONE ) {
 PurpleProxyInfo * pi = purple_global_proxy_get_info ( ) ;
 switch ( proxytype ) {
 case PROXY_SOCKS4A : case PROXY_SOCKS4 : purple_proxy_info_set_type ( pi , PURPLE_PROXY_SOCKS4 ) ;
 break ;
 case PROXY_SOCKS5 : purple_proxy_info_set_type ( pi , PURPLE_PROXY_SOCKS5 ) ;
 break ;
 case PROXY_HTTP : purple_proxy_info_set_type ( pi , PURPLE_PROXY_HTTP ) ;
 break ;
 }
 purple_proxy_info_set_host ( pi , proxyhost ) ;
 purple_proxy_info_set_port ( pi , proxyport ) ;
 purple_proxy_info_set_username ( pi , proxyuser ) ;
 purple_proxy_info_set_password ( pi , proxypass ) ;
 }
 purple_set_blist ( purple_blist_new ( ) ) ;
 purple_signal_connect ( purple_conversations_get_handle ( ) , "buddy-typing" , & funcs , PURPLE_CALLBACK ( prplcb_buddy_typing ) , NULL ) ;
 purple_signal_connect ( purple_conversations_get_handle ( ) , "buddy-typed" , & funcs , PURPLE_CALLBACK ( prplcb_buddy_typing ) , NULL ) ;
 purple_signal_connect ( purple_conversations_get_handle ( ) , "buddy-typing-stopped" , & funcs , PURPLE_CALLBACK ( prplcb_buddy_typing ) , NULL ) ;
 memset ( & funcs , 0 , sizeof ( funcs ) ) ;
 funcs . login = purple_login ;
 funcs . init = purple_init ;
 funcs . logout = purple_logout ;
 funcs . buddy_msg = purple_buddy_msg ;
 funcs . away_states = purple_away_states ;
 funcs . set_away = purple_set_away ;
 funcs . add_buddy = purple_add_buddy ;
 funcs . remove_buddy = purple_remove_buddy ;
 funcs . add_permit = purple_add_permit ;
 funcs . add_deny = purple_add_deny ;
 funcs . rem_permit = purple_rem_permit ;
 funcs . rem_deny = purple_rem_deny ;
 funcs . get_info = purple_get_info ;
 funcs . keepalive = purple_keepalive ;
 funcs . send_typing = purple_send_typing ;
 funcs . handle_cmp = g_strcasecmp ;
 funcs . chat_msg = purple_chat_msg ;
 funcs . chat_with = purple_chat_with ;
 funcs . chat_invite = purple_chat_invite ;
 funcs . chat_topic = purple_chat_set_topic ;
 funcs . chat_kick = purple_chat_kick ;
 funcs . chat_leave = purple_chat_leave ;
 funcs . chat_join = purple_chat_join ;
 funcs . chat_list = purple_chat_list ;
 funcs . transfer_request = purple_transfer_request ;
 help = g_string_new ( "BitlBee libpurple module supports the following IM protocols:\n" ) ;
 for ( prots = purple_plugins_get_protocols ( ) ;
 prots ;
 prots = prots -> next ) {
 PurplePlugin * prot = prots -> data ;
 struct prpl * ret ;
 if ( find_protocol ( prot -> info -> id ) ) {
 continue ;
 }
 ret = g_memdup ( & funcs , sizeof ( funcs ) ) ;
 ret -> name = ret -> data = prot -> info -> id ;
 if ( strncmp ( ret -> name , "prpl-" , 5 ) == 0 ) {
 ret -> name += 5 ;
 }
 register_protocol ( ret ) ;
 g_string_append_printf ( help , "\n* %s (%s)" , ret -> name , prot -> info -> name ) ;
 if ( g_strcasecmp ( prot -> info -> id , "prpl-aim" ) == 0 ) {
 ret = g_memdup ( & funcs , sizeof ( funcs ) ) ;
 ret -> name = "oscar" ;
 ret -> data = NULL ;
 register_protocol ( ret ) ;
 }
 }
 g_string_append ( help , "\n\nFor used protocols, more information about available " "settings can be found using \x02help purple <protocol name>\x02 " "(create an account using that protocol first!)" ) ;
 help_add_mem ( & global . help , "purple" , help -> str ) ;
 g_string_free ( help , TRUE ) ;
 }