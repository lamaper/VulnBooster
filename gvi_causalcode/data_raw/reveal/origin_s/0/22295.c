static void prplcb_roomlist_add_room ( PurpleRoomlist * list , PurpleRoomlistRoom * room ) {
 bee_chat_info_t * ci ;
 const char * title ;
 const char * topic ;
 GList * fields ;
 struct purple_roomlist_data * rld = list -> ui_data ;
 fields = purple_roomlist_room_get_fields ( room ) ;
 title = purple_roomlist_room_get_name ( room ) ;
 if ( rld -> topic >= 0 ) {
 topic = g_list_nth_data ( fields , rld -> topic ) ;
 }
 else {
 topic = NULL ;
 }
 ci = g_new ( bee_chat_info_t , 1 ) ;
 ci -> title = g_strdup ( title ) ;
 ci -> topic = g_strdup ( topic ) ;
 rld -> chats = g_slist_prepend ( rld -> chats , ci ) ;
 }