static void complete_from_nicklist ( GList * * outlist , CHANNEL_REC * channel , const char * nick , const char * suffix , const int match_case ) {
 MODULE_CHANNEL_REC * mchannel ;
 GSList * tmp ;
 GList * ownlist ;
 char * str ;
 int len ;
 ownlist = NULL ;
 len = strlen ( nick ) ;
 mchannel = MODULE_DATA ( channel ) ;
 for ( tmp = mchannel -> lastmsgs ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 LAST_MSG_REC * rec = tmp -> data ;
 if ( ( match_case ? strncmp ( rec -> nick , nick , len ) : g_ascii_strncasecmp ( rec -> nick , nick , len ) ) == 0 && ( match_case ? glist_find_string ( * outlist , rec -> nick ) : glist_find_icase_string ( * outlist , rec -> nick ) ) == NULL ) {
 str = g_strconcat ( rec -> nick , suffix , NULL ) ;
 if ( completion_lowercase ) ascii_strdown ( str ) ;
 if ( rec -> own ) ownlist = g_list_append ( ownlist , str ) ;
 else * outlist = g_list_append ( * outlist , str ) ;
 }
 }
 * outlist = g_list_concat ( ownlist , * outlist ) ;
 }