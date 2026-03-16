static void purple_sync_settings ( account_t * acc , PurpleAccount * pa ) {
 PurplePlugin * prpl = purple_plugins_find_with_id ( pa -> protocol_id ) ;
 PurplePluginProtocolInfo * pi = prpl -> info -> extra_info ;
 GList * i ;
 for ( i = pi -> protocol_options ;
 i ;
 i = i -> next ) {
 PurpleAccountOption * o = i -> data ;
 const char * name ;
 set_t * s ;
 name = purple_account_option_get_setting ( o ) ;
 s = set_find ( & acc -> set , name ) ;
 if ( s -> value == NULL ) {
 continue ;
 }
 switch ( purple_account_option_get_type ( o ) ) {
 case PURPLE_PREF_STRING : case PURPLE_PREF_STRING_LIST : purple_account_set_string ( pa , name , set_getstr ( & acc -> set , name ) ) ;
 break ;
 case PURPLE_PREF_INT : purple_account_set_int ( pa , name , set_getint ( & acc -> set , name ) ) ;
 break ;
 case PURPLE_PREF_BOOLEAN : purple_account_set_bool ( pa , name , set_getbool ( & acc -> set , name ) ) ;
 break ;
 default : break ;
 }
 }
 if ( pi -> options & OPT_PROTO_MAIL_CHECK ) {
 purple_account_set_check_mail ( pa , set_getbool ( & acc -> set , "mail_notifications" ) ) ;
 }
 }