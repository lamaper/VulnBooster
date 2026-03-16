void purple_chat_list ( struct im_connection * ic , const char * server ) {
 PurpleRoomlist * list ;
 struct purple_data * pd = ic -> proto_data ;
 PurplePlugin * prpl = purple_plugins_find_with_id ( pd -> account -> protocol_id ) ;
 PurplePluginProtocolInfo * pi = prpl -> info -> extra_info ;
 if ( ! pi || ! pi -> roomlist_get_list ) {
 imcb_log ( ic , "Room listing unsupported by this purple plugin" ) ;
 return ;
 }
 g_free ( pd -> chat_list_server ) ;
 pd -> chat_list_server = ( server && * server ) ? g_strdup ( server ) : NULL ;
 list = purple_roomlist_get_list ( pd -> account -> gc ) ;
 if ( list ) {
 struct purple_roomlist_data * rld = list -> ui_data ;
 rld -> initialized = TRUE ;
 purple_roomlist_ref ( list ) ;
 }
 }