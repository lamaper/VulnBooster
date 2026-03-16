static GList * completion_channel_nicks ( CHANNEL_REC * channel , const char * nick , const char * suffix ) {
 GSList * nicks , * tmp ;
 GList * list ;
 char * str ;
 int len , match_case ;
 g_return_val_if_fail ( channel != NULL , NULL ) ;
 g_return_val_if_fail ( nick != NULL , NULL ) ;
 if ( * nick == '\0' ) return NULL ;
 if ( suffix != NULL && * suffix == '\0' ) suffix = NULL ;
 match_case = completion_match_case == COMPLETE_MCASE_ALWAYS || ( completion_match_case == COMPLETE_MCASE_AUTO && contains_uppercase ( nick ) ) ;
 list = NULL ;
 complete_from_nicklist ( & list , channel , nick , suffix , match_case ) ;
 len = strlen ( nick ) ;
 nicks = nicklist_getnicks ( channel ) ;
 for ( tmp = nicks ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 NICK_REC * rec = tmp -> data ;
 if ( ( match_case ? strncmp ( rec -> nick , nick , len ) : g_ascii_strncasecmp ( rec -> nick , nick , len ) ) == 0 && rec != channel -> ownnick ) {
 str = g_strconcat ( rec -> nick , suffix , NULL ) ;
 if ( completion_lowercase ) ascii_strdown ( str ) ;
 if ( glist_find_icase_string ( list , str ) == NULL ) list = g_list_append ( list , str ) ;
 else g_free ( str ) ;
 }
 }
 g_slist_free ( nicks ) ;
 if ( ! completion_strict ) list = g_list_concat ( list , completion_nicks_nonstrict ( channel , nick , suffix , match_case ) ) ;
 return list ;
 }