struct groupchat * purple_chat_join ( struct im_connection * ic , const char * room , const char * nick , const char * password , set_t * * sets ) {
 struct purple_data * pd = ic -> proto_data ;
 PurplePlugin * prpl = purple_plugins_find_with_id ( pd -> account -> protocol_id ) ;
 PurplePluginProtocolInfo * pi = prpl -> info -> extra_info ;
 GHashTable * chat_hash ;
 PurpleConversation * conv ;
 struct groupchat * gc ;
 GList * info , * l ;
 if ( ! pi -> chat_info || ! pi -> chat_info_defaults || ! ( info = pi -> chat_info ( purple_account_get_connection ( pd -> account ) ) ) ) {
 imcb_error ( ic , "Joining chatrooms not supported by this protocol" ) ;
 return NULL ;
 }
 if ( ( conv = purple_find_conversation_with_account ( PURPLE_CONV_TYPE_CHAT , room , pd -> account ) ) ) {
 purple_conversation_destroy ( conv ) ;
 }
 chat_hash = pi -> chat_info_defaults ( purple_account_get_connection ( pd -> account ) , room ) ;
 for ( l = info ;
 l ;
 l = l -> next ) {
 struct proto_chat_entry * pce = l -> data ;
 if ( strcmp ( pce -> identifier , "handle" ) == 0 ) {
 g_hash_table_replace ( chat_hash , "handle" , g_strdup ( nick ) ) ;
 }
 else if ( strcmp ( pce -> identifier , "password" ) == 0 ) {
 g_hash_table_replace ( chat_hash , "password" , g_strdup ( password ) ) ;
 }
 else if ( strcmp ( pce -> identifier , "passwd" ) == 0 ) {
 g_hash_table_replace ( chat_hash , "passwd" , g_strdup ( password ) ) ;
 }
 g_free ( pce ) ;
 }
 g_list_free ( info ) ;
 gc = imcb_chat_new ( ic , room ) ;
 serv_join_chat ( purple_account_get_connection ( pd -> account ) , chat_hash ) ;
 g_hash_table_destroy ( chat_hash ) ;
 return gc ;
 }