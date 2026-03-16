static void prplcb_roomlist_in_progress ( PurpleRoomlist * list , gboolean in_progress ) {
 struct im_connection * ic ;
 struct purple_data * pd ;
 struct purple_roomlist_data * rld = list -> ui_data ;
 if ( in_progress || ! rld ) {
 return ;
 }
 ic = purple_ic_by_pa ( list -> account ) ;
 imcb_chat_list_free ( ic ) ;
 pd = ic -> proto_data ;
 g_free ( pd -> chat_list_server ) ;
 pd -> chat_list_server = NULL ;
 ic -> chatlist = g_slist_reverse ( rld -> chats ) ;
 rld -> chats = NULL ;
 imcb_chat_list_finish ( ic ) ;
 if ( rld -> initialized ) {
 purple_roomlist_unref ( list ) ;
 }
 }