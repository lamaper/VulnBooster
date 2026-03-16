struct groupchat * purple_chat_with ( struct im_connection * ic , char * who ) {
 struct purple_data * pd = ic -> proto_data ;
 PurplePlugin * prpl = purple_plugins_find_with_id ( pd -> account -> protocol_id ) ;
 PurplePluginProtocolInfo * pi = prpl -> info -> extra_info ;
 PurpleBuddy * pb = purple_find_buddy ( pd -> account , who ) ;
 PurpleMenuAction * mi ;
 GList * menu ;
 void ( * callback ) ( PurpleBlistNode * , gpointer ) ;
 if ( ! pb || ! pi || ! pi -> blist_node_menu ) {
 return NULL ;
 }
 menu = pi -> blist_node_menu ( & pb -> node ) ;
 while ( menu ) {
 mi = menu -> data ;
 if ( purple_menu_cmp ( mi -> label , "initiate chat" ) || purple_menu_cmp ( mi -> label , "initiate conference" ) ) {
 break ;
 }
 menu = menu -> next ;
 }
 if ( menu == NULL ) {
 return NULL ;
 }
 callback = ( void * ) mi -> callback ;
 callback ( & pb -> node , mi -> data ) ;
 return NULL ;
 }