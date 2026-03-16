static void * prplcb_notify_userinfo ( PurpleConnection * gc , const char * who , PurpleNotifyUserInfo * user_info ) {
 struct im_connection * ic = purple_ic_by_gc ( gc ) ;
 GString * info = g_string_new ( "" ) ;
 GList * l = purple_notify_user_info_get_entries ( user_info ) ;
 char * key ;
 const char * value ;
 int n ;
 while ( l ) {
 PurpleNotifyUserInfoEntry * e = l -> data ;
 switch ( purple_notify_user_info_entry_get_type ( e ) ) {
 case PURPLE_NOTIFY_USER_INFO_ENTRY_PAIR : case PURPLE_NOTIFY_USER_INFO_ENTRY_SECTION_HEADER : key = g_strdup ( purple_notify_user_info_entry_get_label ( e ) ) ;
 value = purple_notify_user_info_entry_get_value ( e ) ;
 if ( key ) {
 strip_html ( key ) ;
 g_string_append_printf ( info , "%s: " , key ) ;
 if ( value ) {
 n = strlen ( value ) - 1 ;
 while ( g_ascii_isspace ( value [ n ] ) ) {
 n -- ;
 }
 g_string_append_len ( info , value , n + 1 ) ;
 }
 g_string_append_c ( info , '\n' ) ;
 g_free ( key ) ;
 }
 break ;
 case PURPLE_NOTIFY_USER_INFO_ENTRY_SECTION_BREAK : g_string_append ( info , "------------------------\n" ) ;
 break ;
 }
 l = l -> next ;
 }
 imcb_log ( ic , "User %s info:\n%s" , who , info -> str ) ;
 g_string_free ( info , TRUE ) ;
 return NULL ;
 }