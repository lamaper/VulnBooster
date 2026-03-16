static GList * completion_nicks_nonstrict ( CHANNEL_REC * channel , const char * nick , const char * suffix , const int match_case ) {
 GSList * nicks , * tmp ;
 GList * list ;
 char * tnick , * str , * in , * out ;
 int len , str_len , tmplen ;
 g_return_val_if_fail ( channel != NULL , NULL ) ;
 list = NULL ;
 len = strlen ( nick ) ;
 nicks = nicklist_getnicks ( channel ) ;
 str_len = 80 ;
 str = g_malloc ( str_len + 1 ) ;
 for ( tmp = nicks ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 NICK_REC * rec = tmp -> data ;
 tmplen = strlen ( rec -> nick ) ;
 if ( tmplen > str_len ) {
 str_len = tmplen * 2 ;
 str = g_realloc ( str , str_len + 1 ) ;
 }
 in = rec -> nick ;
 out = str ;
 while ( * in != '\0' ) {
 if ( i_isalnum ( * in ) ) * out ++ = * in ;
 in ++ ;
 }
 * out = '\0' ;
 if ( ( match_case ? strncmp ( str , nick , len ) : g_ascii_strncasecmp ( str , nick , len ) ) == 0 ) {
 tnick = g_strconcat ( rec -> nick , suffix , NULL ) ;
 if ( completion_lowercase ) ascii_strdown ( tnick ) ;
 if ( glist_find_icase_string ( list , tnick ) == NULL ) list = g_list_append ( list , tnick ) ;
 else g_free ( tnick ) ;
 }
 }
 g_free ( str ) ;
 g_slist_free ( nicks ) ;
 return list ;
 }