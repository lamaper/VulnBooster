static void cmd_network_list ( void ) {
 GString * str ;
 GSList * tmp ;
 str = g_string_new ( NULL ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTCRAP , IRCTXT_NETWORK_HEADER ) ;
 for ( tmp = chatnets ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 IRC_CHATNET_REC * rec = tmp -> data ;
 if ( ! IS_IRCNET ( rec ) ) continue ;
 g_string_truncate ( str , 0 ) ;
 if ( rec -> nick != NULL ) g_string_append_printf ( str , "nick: %s, " , rec -> nick ) ;
 if ( rec -> alternate_nick != NULL ) g_string_append_printf ( str , "alternate_nick: %s, " , rec -> alternate_nick ) ;
 if ( rec -> username != NULL ) g_string_append_printf ( str , "username: %s, " , rec -> username ) ;
 if ( rec -> realname != NULL ) g_string_append_printf ( str , "realname: %s, " , rec -> realname ) ;
 if ( rec -> own_host != NULL ) g_string_append_printf ( str , "host: %s, " , rec -> own_host ) ;
 if ( rec -> autosendcmd != NULL ) g_string_append_printf ( str , "autosendcmd: %s, " , rec -> autosendcmd ) ;
 if ( rec -> usermode != NULL ) g_string_append_printf ( str , "usermode: %s, " , rec -> usermode ) ;
 if ( rec -> sasl_mechanism != NULL ) g_string_append_printf ( str , "sasl_mechanism: %s, " , rec -> sasl_mechanism ) ;
 if ( rec -> sasl_username != NULL ) g_string_append_printf ( str , "sasl_username: %s, " , rec -> sasl_username ) ;
 if ( rec -> sasl_password != NULL ) g_string_append_printf ( str , "sasl_password: (pass), " ) ;
 if ( rec -> cmd_queue_speed > 0 ) g_string_append_printf ( str , "cmdspeed: %d, " , rec -> cmd_queue_speed ) ;
 if ( rec -> max_cmds_at_once > 0 ) g_string_append_printf ( str , "cmdmax: %d, " , rec -> max_cmds_at_once ) ;
 if ( rec -> max_query_chans > 0 ) g_string_append_printf ( str , "querychans: %d, " , rec -> max_query_chans ) ;
 if ( rec -> max_kicks > 0 ) g_string_append_printf ( str , "max_kicks: %d, " , rec -> max_kicks ) ;
 if ( rec -> max_msgs > 0 ) g_string_append_printf ( str , "max_msgs: %d, " , rec -> max_msgs ) ;
 if ( rec -> max_modes > 0 ) g_string_append_printf ( str , "max_modes: %d, " , rec -> max_modes ) ;
 if ( rec -> max_whois > 0 ) g_string_append_printf ( str , "max_whois: %d, " , rec -> max_whois ) ;
 if ( str -> len > 1 ) g_string_truncate ( str , str -> len - 2 ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTCRAP , IRCTXT_NETWORK_LINE , rec -> name , str -> str ) ;
 }
 g_string_free ( str , TRUE ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTCRAP , IRCTXT_NETWORK_FOOTER ) ;
 }